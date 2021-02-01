/** \file
 * Header file that exports only a single function which is used to embed the
 * cppwrapper module into the python interpreter.
 */
#ifndef __CPPWRAPPER_H__
#define __CPPWRAPPER_H__

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include "PythonInterface.h"


/** Announce the cppwrapper module to the python interpreter.
 *
 * Call this method with PyImport_AppendInittab(...) in order to annouce the
 * cppwrapper module to the python interpreter. The module is encapusled within
 * cppwrapper.py.
 */
PyMODINIT_FUNC PyInit_cppwrapper_emb(void);


#endif
