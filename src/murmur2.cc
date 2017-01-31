#include <Python.h>
#include <numpy/arrayobject.h>
#include <stdint.h>
#include <sstream>
#include <string>
#include "../include/MurmurHash2.h"

// Murmur2 64 bit aligned
static char murmur64a_docstring[] = "This function that is given a key returns a 64-bit unsigned integer";
static PyObject* murmur2_murmur64a(PyObject* self, PyObject* args){
        const void* key = NULL;
        int len;
        uint64_t seed, hashvalue;

        if(!PyArg_ParseTuple(args,"sil",&key,&len,&seed))
            return NULL;

        hashvalue = MurmurHash64A(key,len,seed);
        return Py_BuildValue("k",hashvalue);
}

// Murmur2 32 bit neutral
static char murmur32n_docstring[] = "This function that is given a key returns a 32-bit unsigned integer";
static PyObject* murmur2_murmur32n(PyObject* self, PyObject* args){
        const void* key = NULL;
        int len;
        uint32_t seed, hashvalue;

        if(!PyArg_ParseTuple(args,"sii",&key,&len,&seed))
            return NULL;

        hashvalue = MurmurHashNeutral2(key,len,seed);
        return Py_BuildValue("k",hashvalue);
}

// Python module interface
static char module_docstring[] = "This module provides murmur2 hashing functions.";
static PyMethodDef module_methods[] = {
    {"murmur64a", murmur2_murmur64a, METH_VARARGS, murmur64a_docstring},
    {"murmur32n", murmur2_murmur32n, METH_VARARGS, murmur32n_docstring},
    {NULL, NULL, 0, NULL}
};

PyMODINIT_FUNC initmurmur2(void){
    PyObject *m = Py_InitModule3("murmur2", module_methods, module_docstring);

    if(m==NULL)
        return;

    import_array();
}
