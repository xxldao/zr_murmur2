from distutils.core import setup, Extension
from distutils.sysconfig import get_python_inc

setup(
    name='murmur2',
    version='2.1.0',
    ext_modules=[
        Extension(
            "murmur2",
            [
                "src/murmur2.cc",
                "src/MurmurHash2.cpp",
            ],
            include_dirs=[
                get_python_inc(),
                'include/'
            ],

        )
    ],
    url="https://github.com/gsmcwhirter/murmur2",
    author="Gregory McWhirter (based on work by Nobutaka Ito)",
    author_email="greg@ideafreemonoid.org",
    description="murmur2 python wrapper"
)
