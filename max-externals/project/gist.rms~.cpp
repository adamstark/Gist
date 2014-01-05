/**
	@file
	gist.rms~: a root mean square Max object
	by Adam Stark
	@ingroup examples	
*/

#include "ext.h"			// standard Max include, always required (except in Jitter)
#include "ext_obex.h"		// required for "new" style objects
#include "z_dsp.h"			// required for MSP objects
#include "../../src/Gist.h"


//=================================================================================
// struct to represent the object's state
typedef struct _gistmaxobj {
	t_pxobject		ob;			// the object itself (t_pxobject in MSP instead of t_object)
    void			*analysisdataout;
    CoreTimeDomainFeatures<double> *tdf;

} t_gistmaxobj;


//=================================================================================
// method prototypes
void *gistmaxobj_new(t_symbol *s, long argc, t_atom *argv);
void gistmaxobj_free(t_gistmaxobj *x);
void gistmaxobj_assist(t_gistmaxobj *x, void *b, long m, long a, char *s);
void gistmaxobj_float(t_gistmaxobj *x, double f);
void gistmaxobj_dsp(t_gistmaxobj *x, t_signal **sp, short *count);
void gistmaxobj_dsp64(t_gistmaxobj *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags);
t_int *gistmaxobj_perform(t_int *w);
void gistmaxobj_perform64(t_gistmaxobj *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam);

//=================================================================================
void gistmaxobj_outletdata(t_gistmaxobj *x, double v);
void gistmaxobj_freeall(t_gistmaxobj *x);

// global class pointer variable
static t_class *gistmaxobj_class = NULL;


//=================================================================================
int C74_EXPORT main(void)
{	
	// object initialization, note the use of dsp_free for the freemethod, which is required
	// unless you need to free allocated memory, in which case you should call dsp_free from
	// your custom free function.

	t_class *c = class_new("gist.rms~", (method)gistmaxobj_new, (method)gistmaxobj_freeall, (long)sizeof(t_gistmaxobj), 0L, A_GIMME, 0);
	
	//class_addmethod(c, (method)gistmaxobj_float,		"float",	A_FLOAT, 0);
	class_addmethod(c, (method)gistmaxobj_dsp,		"dsp",		A_CANT, 0);		// Old 32-bit MSP dsp chain compilation for Max 5 and earlier
	class_addmethod(c, (method)gistmaxobj_dsp64,		"dsp64",	A_CANT, 0);		// New 64-bit MSP dsp chain compilation for Max 6
	class_addmethod(c, (method)gistmaxobj_assist,	"assist",	A_CANT, 0);
	
	class_dspinit(c);
	class_register(CLASS_BOX, c);
	gistmaxobj_class = c;

	return 0;
}

//=================================================================================
void gistmaxobj_freeall(t_gistmaxobj *x)
{
    delete x->tdf;
    
    dsp_free((t_pxobject *)x);
}

//=================================================================================
void *gistmaxobj_new(t_symbol *s, long argc, t_atom *argv)
{
	t_gistmaxobj *x = (t_gistmaxobj *)object_alloc(gistmaxobj_class);

	if (x) {
		dsp_setup((t_pxobject *)x, 1);	// MSP inlets: arg is # of inlets and is REQUIRED! 
										// use 0 if you don't need inlets
		x->analysisdataout = floatout(x);
        
        
        x->tdf = new CoreTimeDomainFeatures<double>();
        
        
        post("gist.rms~ - by Adam Stark, based on version %s of Gist",GIST_VERSION);
	}
	return (x);
}


//=================================================================================
// NOT CALLED!, we use dsp_free for a generic free function
void gistmaxobj_free(t_gistmaxobj *x) 
{
	;
}

//=================================================================================
void gistmaxobj_assist(t_gistmaxobj *x, void *b, long m, long a, char *s)
{
	if (m == ASSIST_INLET) { //inlet
		sprintf(s, "I am inlet %ld", a);
	} 
	else {	// outlet
		sprintf(s, "I am outlet %ld", a); 			
	}
}


//=================================================================================
// this function is called when the DAC is enabled, and "registers" a function for the signal chain in Max 5 and earlier.
// In this case we register the 32-bit, "gistmaxobj_perform" method.
void gistmaxobj_dsp(t_gistmaxobj *x, t_signal **sp, short *count)
{
	//post("my sample rate is: %f", sp[0]->s_sr);
	
	// dsp_add
	// 1: (t_perfroutine p) perform method
	// 2: (long argc) number of args to your perform method
	// 3...: argc additional arguments, all must be sizeof(pointer) or long
	// these can be whatever, so you might want to include your object pointer in there
	// so that you have access to the info, if you need it.
    dsp_add(gistmaxobj_perform, 3, x, sp[0]->s_vec, sp[0]->s_n);
}


//=================================================================================
// this is the Max 6 version of the dsp method -- it registers a function for the signal chain in Max 6,
// which operates on 64-bit audio signals.
void gistmaxobj_dsp64(t_gistmaxobj *x, t_object *dsp64, short *count, double samplerate, long maxvectorsize, long flags)
{
	//post("my sample rate is: %f", samplerate);
	
	// instead of calling dsp_add(), we send the "dsp_add64" message to the object representing the dsp chain
	// the arguments passed are:
	// 1: the dsp64 object passed-in by the calling function
	// 2: the symbol of the "dsp_add64" message we are sending
	// 3: a pointer to your object
	// 4: a pointer to your 64-bit perform method
	// 5: flags to alter how the signal chain handles your object -- just pass 0
	// 6: a generic pointer that you can use to pass any additional data to your perform method
	
	object_method(dsp64, gensym("dsp_add64"), x, gistmaxobj_perform64, 0, NULL);
}


//=================================================================================
// this is the 32-bit perform method for Max 5 and earlier
t_int *gistmaxobj_perform(t_int *w)
{
	// DO NOT CALL post IN HERE, but you can call defer_low (not defer)
	
	// args are in a vector, sized as specified in gistmaxobj_dsp method
	// w[0] contains &gistmaxobj_perform, so we start at w[1]
	t_gistmaxobj *x = (t_gistmaxobj *)(w[1]);
	t_float *inL = (t_float *)(w[2]);
	int n = (int)w[3];
	
	///----------------------------------------------
    std::vector<double> frame;
    
    for (int i = 0;i < n;i++)
    {
        frame.push_back((double) inL[i]);
    }
	
    double peak = x->tdf->rootMeanSquare(frame);
    
    gistmaxobj_outletdata(x, peak);
    
    //----------------------------------------------
		
	// you have to return the NEXT pointer in the array OR MAX WILL CRASH
	return w + 4;
}


//=================================================================================
// this is 64-bit perform method for Max 6
void gistmaxobj_perform64(t_gistmaxobj *x, t_object *dsp64, double **ins, long numins, double **outs, long numouts, long sampleframes, long flags, void *userparam)
{
	t_double *inL = ins[0];		// we get audio for each inlet of the object from the **ins argument
	
	int n = sampleframes;
	   
    //----------------------------------------------
    double rms = x->tdf->rootMeanSquare(inL,n);
    
    gistmaxobj_outletdata(x,rms);
    //----------------------------------------------
}

//=================================================================================
void gistmaxobj_outletdata(t_gistmaxobj *x, double value)
{
    outlet_float(x->analysisdataout, value);
}
