from distutils.core import setup, Extension
import numpy.distutils.misc_util

setup(
    name='murmur2',
    version='1.1.0',
    ext_modules=[
        Extension(
            "murmur2",
            [
                "src/murmur2.cc",
                "src/MurmurHash2.cpp",
            ],
            include_dirs=[
                numpy.distutils.misc_util.get_numpy_include_dirs()[0],
                'include/'
            ],

        )
    ],
    url="https://github.com/gsmcwhirter/murmur2",
    author="Gregory McWhirter (based on work by Nobutaka Ito)",
    author_email="greg@ideafreemonoid.org",
    description="murmur2 python wrapper"
)

