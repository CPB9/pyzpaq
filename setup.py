import sys
from setuptools import setup, Extension

ss = ['pyzpaq.cpp', 'zpaq/libzpaq.cpp']
if sys.argv[1] == 'sdist':
    ss += ['zpaq/libzpaq.h']

print(ss)    

zpaq = Extension('zpaq',
                  sources = ss,
                  libraries = ['advapi32'] if sys.platform.startswith("win") else [])

setup (name = 'pyzpaq',
       version = '0.1.5',
       description = 'Python zpaq bindings',
       url='https://github.com/CPB9/pyzpaq.git',
       ext_modules = [zpaq])