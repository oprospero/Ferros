from distutils.core import setup, Extension

module1 = Extension('ArduCam',
                    include_dirs = [''],
                    libraries = [''],
                    sources = ['arducam.c'])

setup (name = 'ArduCamModule',
       version = '1.0',
       description = 'Wrapper module for ArduCam',
       author = 'Prosper Van',
       author_email = 'N/A',
       url = 'N/A',
       long_description = '''
This is really just a demo package.
''',
       ext_modules = [module1])