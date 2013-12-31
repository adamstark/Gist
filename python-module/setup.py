# setup.py
# build command : python setup.py build build_ext --inplace
from numpy.distutils.core import setup, Extension
import os, numpy

moduleName = 'gist'
sources = ['Gist_PythonModule.cpp',
'../src/core/CoreTimeDomainFeatures.cpp',
'../src/core/CoreFrequencyDomainFeatures.cpp',
'../src/onset-detection-functions/OnsetDetectionFunction.cpp',
'../src/pitch/Yin.cpp']

include_dirs = [
                numpy.get_include(),'../src'
                ]

setup( name = moduleName,
      include_dirs = include_dirs,
      ext_modules = [Extension(moduleName, sources)]
      )
