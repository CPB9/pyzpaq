from distutils.core import setup, Extension

zpaq = Extension('zpaq',
                  sources = ['pyzpaq.cpp', 'zpaq/libzpaq.cpp'],
                  libraries = ['advapi32'])

setup (name = 'pyzpaq',
       version = '0.1',
       description = 'Python zpaq bindings',
       ext_modules = [zpaq])