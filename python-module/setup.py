# setup.py
# build command : python setup.py build build_ext --inplace
from numpy.distutils.core import setup, Extension
import os, numpy

name = 'gist'
sources = [
'GistPythonModule.cpp',
'../src/Gist.cpp',
'../src/core/CoreFrequencyDomainFeatures.cpp',
'../src/core/CoreTimeDomainFeatures.cpp',
'../src/mfcc/MFCC.cpp',
'../src/onset-detection-functions/OnsetDetectionFunction.cpp',
'../src/pitch/Yin.cpp',
'../src/fft/WindowFunctions.cpp'
]

include_dirs = [
                numpy.get_include(),'/usr/local/include'
                ]

setup( name = 'Gist',
      include_dirs = include_dirs,
      ext_modules = [Extension(name, sources,libraries = ['fftw3'],library_dirs = ['/usr/local/lib'],define_macros=[
                         ('USE_FFTW', None)],)]
      )