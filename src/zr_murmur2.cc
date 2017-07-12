#include <Python.h>
#include <stdint.h>
#include <sstream>
#include <string>
#include "../include/MurmurHash2.h"

const char* ARGS_FMT_64 = "s#|l";
const char* ARGS_FMT_32 = "s#|i";
const char* ARGS_NAMES[] = {"key", "seed", NULL};


// Murmur2 32-bit
static char mmr2_32_docstring[] = "Calculate the unsigned 32-bit MurmurHash2 value.\n\nBeware endian-ness and alignment across platforms.";
static PyObject* murmur2_mmr2_32(PyObject* self, PyObject* args, PyObject* kwargs){
        const char* key = NULL;
        int len;
        uint32_t seed = 0;
        uint32_t hashvalue;

        if(!PyArg_ParseTupleAndKeywords(args, kwargs, ARGS_FMT_32, (char**)ARGS_NAMES, &key, &len, &seed))
            return NULL;

        hashvalue = MurmurHash2((void*)key, len, seed);
        return Py_BuildValue("k", hashvalue);
}

// Murmur2 32 bit alternate (Merkle-Damgard)
static char mmr2_32b_docstring[] = "Calculate the unsigned 32-bit MurmurHash2 value using the Merkle-Damgard construction.\n\nBeware endian-ness and alignment across platforms.";
static PyObject* murmur2_mmr2_32b(PyObject* self, PyObject* args, PyObject* kwargs){
        const char* key = NULL;
        int len;
        uint32_t seed = 0;
        uint32_t hashvalue;

        if(!PyArg_ParseTupleAndKeywords(args, kwargs, ARGS_FMT_32, (char**)ARGS_NAMES, &key, &len, &seed))
            return NULL;

        hashvalue = MurmurHash2A((void*)key, len, seed);
        return Py_BuildValue("k", hashvalue);
}

// Murmur2 32 bit neutral
static char mmr2_32n_docstring[] = "Calculate the unsigned 32-bit MurmurHash2 value.\n\nThis method is endian and alignment neutral but slower.";
static PyObject* murmur2_mmr2_32n(PyObject* self, PyObject* args, PyObject* kwargs){
        const char* key = NULL;
        int len;
        uint32_t seed = 0;
        uint32_t hashvalue;

        if(!PyArg_ParseTupleAndKeywords(args, kwargs, ARGS_FMT_32, (char**)ARGS_NAMES, &key, &len, &seed))
            return NULL;

        hashvalue = MurmurHashNeutral2((void*)key, len, seed);
        return Py_BuildValue("k", hashvalue);
}

// Murmur2 32 bit aligned
static char mmr2_32a_docstring[] = "Calculate the unsigned 32-bit MurmurHash2 value.\nThis variant only does aligned reads, which should be safer on certain platforms.\nBeware endian-ness across platforms.";
static PyObject* murmur2_mmr2_32a(PyObject* self, PyObject* args, PyObject* kwargs){
        const char* key = NULL;
        int len;
        uint32_t seed = 0;
        uint32_t hashvalue;

        if(!PyArg_ParseTupleAndKeywords(args, kwargs, ARGS_FMT_32, (char**)ARGS_NAMES, &key, &len, &seed))
            return NULL;

        hashvalue = MurmurHashAligned2((void*)key, len, seed);
        return Py_BuildValue("k", hashvalue);
}

// Murmur2 64 bit for 64 bit platforms
static char mmr2_64a_docstring[] = "Calculate the unsigned 64-bit MurmurHash2 value for a 64-bit platform.\n\nBeware endian-ness across platforms.";
static PyObject* murmur2_mmr2_64a(PyObject* self, PyObject* args, PyObject* kwargs){
        const char* key = NULL;
        int len;
        uint64_t seed = 0;
        uint64_t hashvalue;

        if(!PyArg_ParseTupleAndKeywords(args, kwargs, ARGS_FMT_64, (char**)ARGS_NAMES, &key, &len, &seed))
            return NULL;

        hashvalue = MurmurHash64A((void*)key, len, seed);
        return Py_BuildValue("k", hashvalue);
}

// Murmur2 64 bit for 32 bit platforms
static char mmr2_64b_docstring[] = "Calculate the unsigned 64-bit MurmurHash2 value for a 32-bit platform.\n\nBeware endian-ness across platforms.";
static PyObject* murmur2_mmr2_64b(PyObject* self, PyObject* args, PyObject* kwargs){
        const char* key = NULL;
        int len;
        uint64_t seed = 0;
        uint64_t hashvalue;

        if(!PyArg_ParseTupleAndKeywords(args, kwargs, ARGS_FMT_64, (char**)ARGS_NAMES, &key, &len, &seed))
            return NULL;

        hashvalue = MurmurHash64B((void*)key, len, seed);
        return Py_BuildValue("k", hashvalue);
}

// Python module interface
static char module_docstring[] = "This module provides murmur2 hashing functions.";
static PyMethodDef module_methods[] = {
    {"hash_32",  (PyCFunction)murmur2_mmr2_32,   METH_VARARGS|METH_KEYWORDS, mmr2_32_docstring},
    {"hash_32a", (PyCFunction)murmur2_mmr2_32a,  METH_VARARGS|METH_KEYWORDS, mmr2_32a_docstring},
    {"hash_32b", (PyCFunction)murmur2_mmr2_32b,  METH_VARARGS|METH_KEYWORDS, mmr2_32b_docstring},
    {"hash_32n", (PyCFunction)murmur2_mmr2_32n,  METH_VARARGS|METH_KEYWORDS, mmr2_32n_docstring},
    {"hash_64a", (PyCFunction)murmur2_mmr2_64a,  METH_VARARGS|METH_KEYWORDS, mmr2_64a_docstring},
    {"hash_64b", (PyCFunction)murmur2_mmr2_64b,  METH_VARARGS|METH_KEYWORDS, mmr2_64b_docstring},
    {NULL, NULL, 0, NULL}
};


// Compatibility for python 2 and 3 -- see http://python3porting.com/cextensions.html
#if PY_MAJOR_VERSION >= 3
#define MOD_ERROR_VAL NULL
#define MOD_SUCCESS_VAL(val) val
#define MOD_INIT(name) PyMODINIT_FUNC PyInit_##name(void)
#define MOD_DEF(ob, name, doc, methods) \
          static struct PyModuleDef moduledef = { PyModuleDef_HEAD_INIT, name, doc, -1, methods, }; \
          ob = PyModule_Create(&moduledef);

#else
#define MOD_ERROR_VAL
  #define MOD_SUCCESS_VAL(val)
  #define MOD_INIT(name) PyMODINIT_FUNC init##name(void)
  #define MOD_DEF(ob, name, doc, methods) \
          ob = Py_InitModule3(name, methods, doc);

#endif


MOD_INIT(zr_murmur2) {
    PyObject *m;

    MOD_DEF(m, "zr_murmur2", module_docstring, module_methods)

    if (m == NULL) return MOD_ERROR_VAL;

    return MOD_SUCCESS_VAL(m);
}


