/** \file
 * Main interface class which gets called by COAST to establish the link.
 */
#ifndef __PYTHONINTERFACE_H__
#define __PYTHONINTERFACE_H__

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include <cstddef>
#include <string>
#include <mutex>
#include "stdfilesystem.h"

#include <crs/CorsikaTypes.h>
#include <crs/CInteraction.h>
#include <crs/CParticle.h>

#include "PythonWrapper.h"
#include "CorsikaConfig.h"


/** Singelton class that handles the Python-COAST interface. */
class PythonInterface : private PythonWrapper {
    
    // singleton handling
    private:
        PythonInterface() = default;
        PythonInterface(const PythonInterface &) = delete;
        PythonInterface & operator=(const PythonInterface &) = delete;
        ~PythonInterface() = default;

        class CGuard {
            public:
                ~CGuard() {
                    if (PythonInterface::_instance != nullptr) {
                        delete PythonInterface::_instance;
                        PythonInterface::_instance = nullptr;
                    }
                }
        };

        static PythonInterface * _instance;


    private:
        CorsikaConfig mCorsikaConfig;

        mutable std::mutex mCaptureWrite_mutex;
        bool mCaptureWrite = true;
        mutable std::mutex mCaptureInteraction_mutex;
        bool mCaptureInteraction = true;
        mutable std::mutex mCaptureTrack_mutex;
        bool mCaptureTrack = true;

        const std::string mInterfaceName = "interface";
        PyObject * mPython_module_interface = NULL;
        const std::string mCppAccessName = "instance";
        PyObject * mPython_class_cppaccess = NULL;
        const std::string mCppAccessInitName = "_init";
        const std::string mCppAccessCloseName = "_close";
        const std::string mCppAccessWriteName = "_write";
        const std::string mCppAccessInteractionName = "_interaction";
        const std::string mCppAccessTrackName = "_track";

        const std::string mOverrideName = "override.py";
        filesystem::path mOverridePath;


    public:
        /** Get a singleton instance of this class */
        static PythonInterface * instance();

        /** Initialize the interface.
         *
         * Gets called by the COAST function inida_(...).
         *
         * @param config CorsikaConfig information.
         */
        void init(const CorsikaConfig & config);

        /** Write and process a CORSIKA binary data block.
         *
         * Gets called by the COAST function wrida_(...).
         *
         * @param DataSubBlock pointer to a memory area of varying size,
         * depending on the CORSIKA option THIN (thinning).
         * - thinned mode:     39 (Particles) * 8 (Entries) * 4 (Bytes)
         * - not-thinned mode: 39 (Particles) * 7 (Entries) * 4 (Bytes)
         */
        void write(const CREAL * DataSubBlock);

        /** Close and finalize the interface.
         *
         * Gets called by the COAST function cloda_(...).
         */
        void close();

        /** Handle particle interaction information.
         *
         * Gets called by the COAST function interaction_(...).
         *
         * @param info COAST datatype containing interaction info.
         */
        void interaction(const crs::CInteraction & info);

        /** Handle particle track information.
         *
         * Gets called by the COAST function track_(...).
         *
         * @param pre COAST datatype containing particle information at the
         * beginning of the track.
         * @param post COAST datatype containing particle information at the
         * end of the track.
         */
        void track(const crs::CParticle & pre, const crs::CParticle & post);

        /** Set the interface to capture COAST wrida_(...) calls.
         *
         * @param val true = capture; false = do not capture.
         */
        void captureWrite(bool val);

        /** Indicate if the interface is currently capturing COAST wrida_(...)
         * calls.
         *
         * @retval true Interface is currently capturing calls.
         * @retval false Interface is currently not capturing calls.
         */
        bool isCapturingWrite() const;

        /** Set the interface to capture COAST interaction_(...) calls.
         *
         * @param val true = capture; false = do not capture.
         */
        void captureInteraction(bool val);

        /** Indicate if the interface is currently capturing COAST
         * interaction_(...) calls.
         *
         * @retval true Interface is currently capturing calls.
         * @retval false Interface is currently not capturing calls.
         */
        bool isCapturingInteraction() const;

        /** Set the interface to capture COAST track_(...) calls.
         *
         * @param val true = capture; false = do not capture.
         */
        void captureTrack(bool val);
        
        /** Indicate if the interface is currently capturing COAST track_(...)
         * calls.
         *
         * @retval true Interface is currently capturing calls.
         * @retval false Interface is currently not capturing calls.
         */
        bool isCapturingTrack() const;

        /** Return CorsikaConfig information */
        CorsikaConfig getCorsikaConfig() const;


    private:
        void setCorsikaConfig(const CorsikaConfig & config);
        void setupPackagesSearchPath() const;
        void setupOverrideSearchPath();
        void importInterface();
        void runOverride() const;
        void callPythonInit() const;
        void callPythonClose() const;

};


#endif
