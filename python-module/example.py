import numpy as np 
import gist
from pylab import *

x = np.arange (512) / 512.

print "FS: ", gist.getSamplingFrequency()

gist.setSamplingFrequency (48000)
print "FS: ", gist.getSamplingFrequency()

gist.setAudioFrameSize (512)

gist.processFrame (x)

print ""
print "--- CORE TIME DOMAIN FEATURES ---"
print ""
print "RMS:", gist.rms()
print "Peak Energy:", gist.peakEnergy()
print "Zero Crossing Rate:", gist.zeroCrossingRate()
print ""

print "--- CORE FREQUENCY DOMAIN FEATURES ---"
print ""
print "Spectral Centroid: ", gist.spectralCentroid()
print "Spectral Crest:", gist.spectralCrest()
print "Spectral Flatness:", gist.spectralFlatness()
print "Spectral Rolloff:", gist.spectralRolloff()
print "Spectral Kurtosis:", gist.spectralKurtosis()
print ""

print "--- ONSET DETECTION FUNCTIONS ---"
print ""
print "Energy Difference:", gist.energyDifference()
print "Spectral Difference:", gist.spectralDifference()
print "Spectral Difference (half-wave rectified):", gist.spectralDifferenceHWR()
print "Complex Spectral Difference:", gist.complexSpectralDifference()
print "High Frequency Content:", gist.highFrequencyContent()
print ""

print "--- PITCH ---"
print ""
print "Pitch:", gist.pitch()
print ""

print "--- SPECTRA ---"
print ""
magnitudeSpectrum = gist.magnitudeSpectrum()
print "Magnitude Spectrum has", magnitudeSpectrum.size, "samples"

melFrequencySpectrum = gist.melFrequencySpectrum()
print "Mel-Frequency Spectrum has", melFrequencySpectrum.size, "samples"

mfccs = gist.mfccs()
print "MFCCs has", mfccs.size, "samples"


