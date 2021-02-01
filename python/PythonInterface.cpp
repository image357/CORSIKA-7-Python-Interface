#include "PythonInterface.h"

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include <cstddef>
#include <cstdlib>
#include <cstdio>
#include "stdfilesystem.h"
#include <mutex>

#include "CorsikaConfig.h"
#include "CppWrapper.h"


// interface callbacks

void PythonInterface::init(const CorsikaConfig & config) {
    setCorsikaConfig(config);

    PyImport_AppendInittab("cppwrapper_emb", &PyInit_cppwrapper_emb);
    Py_Initialize();
    setupPackagesSearchPath();
    importInterface();
    setupOverrideSearchPath();
    runOverride();
    callPythonInit();
}


void PythonInterface::close() {
    callPythonClose();
    Py_Finalize();
}


void PythonInterface::write([[maybe_unused]] const CREAL * DataSubBlock) {
    if (!isCapturingWrite()) {
        return;
    }

    CorsikaConfig::CorsikaOption thinning = getCorsikaConfig().getThinning();
    int blocklen = 0;
    switch (thinning) {
        case CorsikaConfig::CorsikaOption::TRUE:
            blocklen = 39 * 8 * 4;
            break;

        case CorsikaConfig::CorsikaOption::FALSE:
            blocklen = 39 * 7 * 4;
            break;

        case CorsikaConfig::CorsikaOption::UNKNOWN:
            throw std::runtime_error("corsika option thinning not set");
            break;

        default:
            throw std::domain_error("in write(): unknown corsika option value");
            break;
    }

    PyObject * result = PyObject_CallMethod(
            mPython_class_cppaccess, mCppAccessWriteName.c_str(),
            "y#", (const char *) DataSubBlock, blocklen);

    if (result == NULL) {
        PyErr_Print();
        throw std::runtime_error("error in python call to write()");
    }

    Py_DECREF(result);
}


void PythonInterface::interaction(const crs::CInteraction & info) {
    if (!isCapturingInteraction()) {
        return;
    }

    PyObject * result = PyObject_CallMethod(
            mPython_class_cppaccess, mCppAccessInteractionName.c_str(),
            "d d d d d d i i",
            info.x, info.y, info.z, info.etot, info.sigma, info.kela,
            info.projId, info.targetId);

    if (result == NULL) {
        PyErr_Print();
        throw std::runtime_error("error in python call to interaction()");
    }

    Py_DECREF(result);
}


void PythonInterface::track(const crs::CParticle & pre,
                            const crs::CParticle & post) {
    if (!isCapturingTrack()) {
        return;
    }

    PyObject * result = PyObject_CallMethod(
            mPython_class_cppaccess, mCppAccessTrackName.c_str(),
            "d d d d d d d i i"
            "d d d d d d d i i",
            pre.time,  pre.x,  pre.y,  pre.z,  pre.depth,  pre.energy,
            pre.weight,  pre.particleId,  pre.hadronicGeneration,

            post.time, post.x, post.y, post.z, post.depth, post.energy,
            post.weight, post.particleId, post.hadronicGeneration);

    if (result == NULL) {
        PyErr_Print();
        throw std::runtime_error("error in python call to track()");
    }

    Py_DECREF(result);
}


// singleton setup

PythonInterface * PythonInterface::_instance = nullptr;

PythonInterface * PythonInterface::instance() {
    static CGuard g;
    if (_instance == nullptr) {
        _instance = new PythonInterface();
    }

    return _instance;
}


// member functions

void PythonInterface::captureWrite(bool val) {
    std::scoped_lock<std::mutex> lock(mCaptureWrite_mutex);
    mCaptureWrite = val;
}

bool PythonInterface::isCapturingWrite() const {
    // don't lock just wait for unlock
    std::unique_lock<std::mutex> lock(mCaptureWrite_mutex);
    lock.unlock();
    return mCaptureWrite;
}


void PythonInterface::captureInteraction(bool val) {
    std::scoped_lock<std::mutex> lock(mCaptureInteraction_mutex);
    mCaptureInteraction = val;
}

bool PythonInterface::isCapturingInteraction() const {
    // don't lock just wait for unlock
    std::unique_lock<std::mutex> lock(mCaptureInteraction_mutex);
    lock.unlock();
    return mCaptureInteraction;
}


void PythonInterface::captureTrack(bool val) {
    std::scoped_lock<std::mutex> lock(mCaptureTrack_mutex);
    mCaptureTrack = val;
}

bool PythonInterface::isCapturingTrack() const {
    // don't lock just wait for unlock
    std::unique_lock<std::mutex> lock(mCaptureTrack_mutex);
    lock.unlock();
    return mCaptureTrack;
}


void PythonInterface::setCorsikaConfig(const CorsikaConfig & config) {
    mCorsikaConfig = config;
}

CorsikaConfig PythonInterface::getCorsikaConfig() const {
    return mCorsikaConfig;
}


void PythonInterface::setupPackagesSearchPath() const {
    auto packagesPath = getPackagesPath();
    addPythonSearchPath(packagesPath);
}


void PythonInterface::setupOverrideSearchPath() {
    if (!mOverridePath.empty()) {
        return;
    }

    const char * envval = std::getenv("CORSIKA_PYTHON_INTERFACE");
    if (envval != NULL) {
        filesystem::path pythonPath(envval);
        mOverridePath = pythonPath / mOverrideName;
        if (filesystem::exists(mOverridePath)) {
            addPythonSearchPath(pythonPath);
            return;
        }
    }

    auto coastPath = getCoastPath();
    mOverridePath = coastPath / mOverrideName;
    if (filesystem::exists(mOverridePath)) {
        addPythonSearchPath(coastPath);
        return;
    }

    throw std::runtime_error(
            std::string("cannot find python file ") + mOverrideName);
}


void PythonInterface::importInterface() {
    mPython_module_interface = getPythonModule(mInterfaceName);

    mPython_class_cppaccess = PyObject_GetAttrString(
            mPython_module_interface, mCppAccessName.c_str());

    if (mPython_class_cppaccess == NULL) {
        PyErr_Print();
        throw std::runtime_error(
                std::string("cannot access python object ") + mCppAccessName);
    }
}


void PythonInterface::runOverride() const {
    int retval = runPythonFile(mOverridePath);
    if (retval != 0) {
        if (PyErr_Occurred() != NULL) {
            PyErr_Print();
        }
        throw std::runtime_error(
                std::string("unhandled exception in ") + mOverrideName);
    }
}


void PythonInterface::callPythonInit() const {
    PyObject * result = PyObject_CallMethod(
            mPython_class_cppaccess, mCppAccessInitName.c_str(), NULL);

    if (result == NULL) {
        PyErr_Print();
        throw std::runtime_error("error in python call to init()");
    }

    Py_DECREF(result);
}


void PythonInterface::callPythonClose() const {
    PyObject * result = PyObject_CallMethod(
            mPython_class_cppaccess, mCppAccessCloseName.c_str(), NULL);

    if (result == NULL) {
        PyErr_Print();
        throw std::runtime_error("error in python call to close()");
    }

    Py_DECREF(result);
    Py_XDECREF(mPython_module_interface);
    Py_XDECREF(mPython_class_cppaccess);
}

