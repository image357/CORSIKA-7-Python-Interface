"""Interface module for handling, reading and writing CORSIKA information
based on the COAST interface.
"""

from .cppaccess import CppAccess
from .cppwrapper import disableWrite, enableWrite, \
                        disableInteraction, enableInteraction, \
                        disableTrack, enableTrack
from .virtual_override import Override
from .interaction import Interaction
from .particle import Particle

instance = CppAccess()
patch = instance.patch

