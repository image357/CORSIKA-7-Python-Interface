/** \file
 * COAST interface definition file.
 *
 * Here you can change the behavior of the COAST interface inside the function
 * inida_(...), cloda_(...), wrida_(...), interaction_(...) and track_(...).
 */
#include <interface/CorsikaInterface.h>

#include <crs/CInteraction.h>
#include <crs/CParticle.h>
#include <crs/CorsikaTypes.h>
#include <crs/TSubBlock.h>

#include "python/PythonInterface.h"
#include "python/CorsikaConfig.h"


/** Initialize the COAST interface. */
extern "C" void inida_ ([[maybe_unused]] const char * filename,
                        [[maybe_unused]] const bool & thinning,
                        [[maybe_unused]] const bool & curved,
                        [[maybe_unused]] const bool & slant,
                        [[maybe_unused]] const bool & stackinput,
                        [[maybe_unused]] const bool & preshower,
                        [[maybe_unused]] int str_length) {
#ifdef USE_PYTHON_INTERFACE
    PythonInterface * pythonInterface = PythonInterface::instance();
    CorsikaConfig config(filename, str_length, thinning, curved, slant,
                         stackinput, preshower);
    pythonInterface->init(config);
#endif
}


/** Write a CORSIKA binary data-block.
 *
 * Data is one CORSIKA data-block consiting of 21 SubBlocks.
 * A SubBlock can be:
 * - thinned mode:     39 (Particles) * 8 (ENTRIES) * 4 (BYTES)
 * - not-thinned mode: 39 (Particles) * 7 (ENTRIES) * 4 (BYTES)
 */
extern "C" void wrida_([[maybe_unused]] const CREAL * DataSubBlock) {
#ifdef USE_PYTHON_INTERFACE
    PythonInterface * pythonInterface = PythonInterface::instance();
    pythonInterface->write(DataSubBlock);
#endif
}


/** Close and finalize the COAST interface. */
extern "C" void cloda_() {
#ifdef USE_PYTHON_INTERFACE
    PythonInterface * pythonInterface = PythonInterface::instance();
    pythonInterface->close();
#endif
}


/** Handle particle interaction information.
 *
 * All interactions in the shower are available in this function!
 * The information available in the CInteraction class are:
 * - double x;
 * - double y;
 * - double z;
 * - double etot;      (lab energy)
 * - double sigma;     (cross-section of process)
 * - double kela;      (elasticity)
 * - int    projId;    (projectile)
 * - int    targetId;  (target)
 */
extern "C" void interaction_([[maybe_unused]] const crs::CInteraction & info) {
#ifdef USE_PYTHON_INTERFACE
    PythonInterface * pythonInterface = PythonInterface::instance();
    pythonInterface->interaction(info);
#endif
}


/** Handle particle track information.
 *
 * All particles in the shower are available in this function!
 * The pre and post objecte are the two endpoints for one single track
 * in the shower, where the information available in CParticle is:
 * - double x;
 * - double y;
 * - double z;
 * - double depth;
 * - double time;
 * - double energy;
 * - double weight;
 * - int    particleId;
 * - int    hadronicGeneration;
 */
extern "C" void track_([[maybe_unused]] const crs::CParticle & pre,
                       [[maybe_unused]] const crs::CParticle & post) {
#ifdef USE_PYTHON_INTERFACE
    PythonInterface * pythonInterface = PythonInterface::instance();
    pythonInterface->track(pre, post);
#endif
}


// for special use only but should be defined because it is delcared in CORSIKA.F
extern "C" void tabularizedatmosphere_(
        [[maybe_unused]] const int & nPoints,
        [[maybe_unused]] const double * height,
        [[maybe_unused]] const double * refractiveIndex) {
}

