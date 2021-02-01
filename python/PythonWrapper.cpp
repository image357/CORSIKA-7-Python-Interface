#include "PythonWrapper.h"

#define PY_SSIZE_T_CLEAN
#include <Python.h>


filesystem::path PythonWrapper::getCoastPath() const {
    if (!mCoastPath.empty()) {
        return mCoastPath;
    }

    const char * envval = std::getenv("COAST_USER_LIB");
    if (envval == NULL) {
        throw std::runtime_error(
                "environment variable COAST_USER_LIB is not set");
    }

    filesystem::path coastPath(envval);
    mCoastPath = coastPath;
    return mCoastPath;
}


filesystem::path PythonWrapper::getPackagesPath() const {
    if (!mPackagesPath.empty()) {
        return mPackagesPath;
    }

    auto packagesPath = getCoastPath() / "python" / "packages";
    mPackagesPath = packagesPath;
    return mPackagesPath;
}


void PythonWrapper::addPythonSearchPath(filesystem::path path) const {
    auto python_path = PyUnicode_FromString(path.c_str());

    auto python_string_sys = PyUnicode_FromString("sys");
    auto python_module_sys = PyImport_Import(python_string_sys);
    auto python_list_path = PyObject_GetAttrString(python_module_sys, "path");
    PyList_Append(python_list_path, python_path);

    Py_DECREF(python_path);
    Py_DECREF(python_string_sys);
    Py_DECREF(python_module_sys);
    Py_DECREF(python_list_path);
}


PyObject * PythonWrapper::getPythonModule(std::string name) const {
    auto python_name = PyUnicode_FromString(name.c_str());
    auto python_module = PyImport_Import(python_name);

    Py_DECREF(python_name);

    if (python_module == NULL) {
        PyErr_Print();
        throw std::runtime_error(
                std::string("cannot import python module ") + name);
    }

    return python_module;
}


void PythonWrapper::importPythonModule(std::string name) const {
    auto python_module = getPythonModule(name);
    Py_DECREF(python_module);
}


int PythonWrapper::runPythonFile(filesystem::path filepath) const {
    std::FILE * file = std::fopen(filepath.c_str(), "r");
    if (file == NULL) {
        throw std::runtime_error(
                std::string("cannot open python runfile ") + filepath.string());
    }

    int retval = PyRun_SimpleFile(file, filepath.filename().c_str());
    std::fclose(file);

    if (retval != 0) {
        if (PyErr_Occurred() != NULL) {
            PyErr_Print();
        }
        throw std::runtime_error(
                std::string("error in python runfile ") + filepath.string());
    }

    return retval;
}

