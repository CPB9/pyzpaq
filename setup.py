from setuptools import setup, Extension

zpaq = Extension('zpaq',
                  sources = ['pyzpaq.cpp', 'zpaq/libzpaq.cpp'],
                  libraries = ['advapi32'])

setup (name = 'pyzpaq',
       version = '0.1.1',
       description = 'Python zpaq bindings',
       url='https://github.com/CPB9/pyzpaq.git',
       ext_modules = [zpaq])