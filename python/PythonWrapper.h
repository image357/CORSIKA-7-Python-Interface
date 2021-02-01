#ifndef __PYTHONWRAPPER_H__
#define __PYTHONWRAPPER_H__

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include "stdfilesystem.h"


/** Utility class for Python C API calls that are used in PythonInterface. */
class PythonWrapper {

    private:
        mutable filesystem::path mCoastPath;
        mutable filesystem::path mPackagesPath;

    public:
        /** Find the COAST_USER_LIB path on system. */
        filesystem::path getCoastPath() const;

        /** Find the python packages responsible for handling the interface. */
        filesystem::path getPackagesPath() const;

        /** Add a given path to the package search path for the internal
         * python interpreter that is used by CORSIKA.
         *
         * @param path std::filesystem path object.
         */
        void addPythonSearchPath(filesystem::path path) const;


        /** Import and get a handle to python module.
         *
         * @param name Python module name that should be imported.
         */
        PyObject * getPythonModule(std::string name) const;

        /** Import a python module without return a handle.
         *
         * @param name Python module name that should be imported.
         */
        void importPythonModule(std::string name) const;

        /** Run a python script within the internal python interpreter that is
         * used by CORSIKA.
         *
         * Throws a std::runtime_error if the file cannot be found or run.
         *
         * @param filepath Path to the python script that should be run.
         *
         * @return Integer returned by the Python C API function
         * PyRun_SimpleFile(...).
         */
        int runPythonFile(filesystem::path filepath) const;

};


#endif
