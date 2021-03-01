import sys
from setuptools import setup, Extension

ss = ['pyzpaq.cpp', 'zpaq/libzpaq.cpp']
if 'sdist' in sys.argv:
    ss += ['zpaq/libzpaq.h']

print(ss)    

zpaq = Extension('zpaq',
                  define_macros = [('unix', '1'), ('BSD', 1)] if sys.platform.startswith("darwin") else [],   
                  sources = ss,
                  libraries = ['advapi32'] if sys.platform.startswith("win") else [])

setup (name = 'pyzpaq',
       version = '0.1.7',
       description = 'Python zpaq bindings',
       url='https://github.com/CPB9/pyzpaq.git',
       ext_modules = [zpaq])
