//=======================================================================
/** @file Gist_PythonModule.cpp
 *  @brief A Python interface for the audio analysis library Gist
 *  @author Adam Stark
 *  @copyright Copyright (C) 2013  Adam Stark
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
//=======================================================================

#include <iostream>
#include <vector>
#include <Python.h>
#include <numpy/arrayobject.h>
#include "../src/Gist.h"

CoreTimeDomainFeatures<double> tdf;

Yin<double> yin(44100);

typedef struct InputData
{
    double* audioSignal;
    long numSamples;
    long frameSize;
    bool chunked;
    bool constructed;
    PyObject *arrayObject;
} inputData;


enum AnalysisId
{
    a_RMS,
    a_PeakEnergy,
    a_PitchYin
};

static void parseInputData(PyObject *dummy, PyObject *args,InputData *inputData)
{
    PyObject *arg1=NULL;
    PyObject *arr1=NULL;
    long frameSize;
    
    // extract input data
    if (PyArg_ParseTuple(args, "O", &arg1))
    {
        // place input array into arr1
        arr1 = PyArray_FROM_OTF(arg1, NPY_DOUBLE, NPY_IN_ARRAY);
        
        inputData->chunked = false;
        inputData->constructed = true;
    }
    else if (PyArg_ParseTuple(args, "Ol", &arg1,&frameSize))
    {
        // place input array into arr1
        arr1 = PyArray_FROM_OTF(arg1, NPY_DOUBLE, NPY_IN_ARRAY);
        
        inputData->chunked = true;
        inputData->constructed = true;

        inputData->frameSize = frameSize;
    }
    else
    {
        inputData->constructed = false;
    }
    
    
    
    if (arr1 == NULL)
    {
        inputData->constructed = false;

    }
    else
    {
        long numSamples = PyArray_Size((PyObject*)arr1);
        
        
        
        inputData->audioSignal = (double*) PyArray_DATA(arr1);
        inputData->numSamples = numSamples;
        inputData->arrayObject = arr1;
    }
}

double processFrameWithAnalysisAlgorithm(double *signal,long numSamples,AnalysisId analysisId)
{
    switch (analysisId) {
        case a_RMS:
        {
            return tdf.rootMeanSquare(signal,numSamples);
            break;
        }
            
        case a_PeakEnergy:
        {
            return tdf.peakEnergy(signal,numSamples);
            break;
        }
            
        case a_PitchYin:
        {
            return yin.pitchYin(signal,numSamples);
            break;
        }
            
        default:
        {
            return 0.0;
            break;
        }
    }
}

static PyObject * executeAnalysis(InputData *inputData,AnalysisId analysisId)
{
    // if for some reason the input data wasn't parsed correctly, or the num samples is 0
    if ((!inputData->constructed) || (inputData->numSamples == 0))
    {
        // then return NULL
        return NULL;
    }
    
    if (inputData->chunked)
    {
        npy_intp length;
        
        double frame[inputData->frameSize];
        
        long numFrames = inputData->numSamples / inputData->frameSize;
        
        double analysisResult[numFrames];
        
        length = numFrames;
        
        PyObject* result = PyArray_SimpleNew(1, &length, NPY_DOUBLE);
        void *array_data = PyArray_DATA((PyArrayObject*)result);
        
        for (int i = 0;i < numFrames;i++)
        {
            for (int j = 0;j < inputData->frameSize;j++)
            {
                frame[j] = inputData->audioSignal[(i*inputData->frameSize) + j];
            }
 
            analysisResult[i] = processFrameWithAnalysisAlgorithm(frame,inputData->frameSize,analysisId);
            
        }
        
        memcpy(array_data, analysisResult, PyArray_ITEMSIZE((PyArrayObject*) result) * length);
     
        return result;
    }
    else
    {
        double result = processFrameWithAnalysisAlgorithm(inputData->audioSignal,inputData->numSamples,analysisId);
        
        return PyFloat_FromDouble(result);
    }
    
    
}

//================================================================
static PyObject * rootMeanSquare(PyObject *dummy, PyObject *args)
{
    // create an inputData object
    InputData inputData;
    
    // parse the input arguments
    parseInputData(dummy,args,&inputData);
    
    return executeAnalysis(&inputData,a_RMS);
}

//================================================================
static PyObject * peakEnergy(PyObject *dummy, PyObject *args)
{
    // create an inputData object
    InputData inputData;
    
    // parse the input arguments
    parseInputData(dummy,args,&inputData);
    
    return executeAnalysis(&inputData,a_PeakEnergy);
}

//================================================================
static PyObject * pitchYin(PyObject *dummy, PyObject *args)
{
    // create an inputData object
    InputData inputData;
    
    // parse the input arguments
    parseInputData(dummy,args,&inputData);
    
    return executeAnalysis(&inputData,a_PitchYin);
}


//================================================================
static PyMethodDef Gist_methods[] = {
    { "rootMeanSquare",rootMeanSquare,METH_VARARGS,"Calculates the Root Mean Square (RMS) of a given input signal"},
    { "peakEnergy",peakEnergy,METH_VARARGS,"Calculates the Peak Energy of a given input signal"},
    { "pitchYin",pitchYin,METH_VARARGS,"Calculates the pitch of a given input signal"},
    {NULL, NULL, 0, NULL} /* Sentinel */
};

//================================================================
PyMODINIT_FUNC initgist(void)
{
    (void)Py_InitModule("gist", Gist_methods);
    import_array();
}

//================================================================
int main(int argc, char *argv[])
{
    /* Pass argv[0] to the Python interpreter */
    Py_SetProgramName(argv[0]);
    
    /* Initialize the Python interpreter.  Required. */
    Py_Initialize();
    
    /* Add a static module */
    initgist();
}


