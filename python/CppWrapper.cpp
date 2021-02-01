#include "CppWrapper.h"

#define PY_SSIZE_T_CLEAN
#include <Python.h>


static PyObject * disableWrite(PyObject * self, PyObject * args);
static PyObject * enableWrite(PyObject * self, PyObject * args);
static PyObject * disableInteraction(PyObject * self, PyObject * args);
static PyObject * enableInteraction(PyObject * self, PyObject * args);
static PyObject * disableTrack(PyObject * self, PyObject * args);
static PyObject * enableTrack(PyObject * self, PyObject * args);


static PyMethodDef cppwrapper_emb_methods[] = {
    {
        "disableWrite",
        disableWrite,
        METH_VARARGS,
        "Disable COAST calls to python write()."
    },
    {
        "enableWrite",
        enableWrite,
        METH_VARARGS,
        "Enable COAST calls to python write()."
    },
    {
        "disableInteraction",
        disableInteraction,
        METH_VARARGS,
        "Disable COAST calls to python interaction()."
    },
    {
        "enableInteraction",
        enableInteraction,
        METH_VARARGS,
        "Enable COAST calls to python interaction()."
    },
    {
        "disableTrack",
        disableTrack,
        METH_VARARGS,
        "Disable COAST calls to python track()."
    },
    {
        "enableTrack",
        enableTrack,
        METH_VARARGS,
        "Enable COAST calls to python track()."
    },

    {NULL, NULL, 0, NULL}
};

static PyModuleDef cppwrapper_emb_module = {
    PyModuleDef_HEAD_INIT,
    "cppwrapper_emb",
    "Gives access to C++ functions of the interface.",
    -1,
    cppwrapper_emb_methods,
    NULL, NULL, NULL, NULL
};

PyMODINIT_FUNC PyInit_cppwrapper_emb(void) {
    return PyModule_Create(&cppwrapper_emb_module);
}


// methods

static PyObject * disableWrite([[maybe_unused]] PyObject * self,
                               [[maybe_unused]] PyObject * args) {
    PythonInterface * pythonInterface = PythonInterface::instance();
    pythonInterface->captureWrite(false);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject * enableWrite([[maybe_unused]] PyObject * self,
                              [[maybe_unused]] PyObject * args) {
    PythonInterface * pythonInterface = PythonInterface::instance();
    pythonInterface->captureWrite(true);

    Py_INCREF(Py_None);
    return Py_None;
}


static PyObject * disableInteraction([[maybe_unused]] PyObject * self,
                                     [[maybe_unused]] PyObject * args) {
    PythonInterface * pythonInterface = PythonInterface::instance();
    pythonInterface->captureInteraction(false);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject * enableInteraction([[maybe_unused]] PyObject * self,
                                    [[maybe_unused]] PyObject * args) {
    PythonInterface * pythonInterface = PythonInterface::instance();
    pythonInterface->captureInteraction(true);

    Py_INCREF(Py_None);
    return Py_None;
}


static PyObject * disableTrack([[maybe_unused]] PyObject * self,
                               [[maybe_unused]] PyObject * args) {
    PythonInterface * pythonInterface = PythonInterface::instance();
    pythonInterface->captureTrack(false);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject * enableTrack([[maybe_unused]] PyObject * self,
                              [[maybe_unused]] PyObject * args) {
    PythonInterface * pythonInterface = PythonInterface::instance();
    pythonInterface->captureTrack(true);

    Py_INCREF(Py_None);
    return Py_None;
}

