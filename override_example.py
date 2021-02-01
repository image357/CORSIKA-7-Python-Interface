"""Example override.py that demonstrates how to use the CORSIKA-python
interface.
"""

import os
import sys

# You do not have to add COAST_USER_LIB/python/packages to your search path
# if you only run the interface within CORSIKA.
packpath = os.path.join(os.environ["COAST_USER_LIB"], "python", "packages")
if packpath not in sys.path:
    sys.path.append(packpath)

# import CORSIKA-COAST-python interface link.
import interface

# Override interface.Override and implement corresponding methods.
class MyInterface(interface.Override):

    def __init__(self):
        print("patched interface")

    def init(self):
        # You can disable and enable the capturing of certain interface parts.
        interface.disableWrite()
        interface.disableInteraction()
        interface.disableTrack()
        pass

    def close(self):
        pass

    def write(self, subblock : bytes):
        pass

    def interaction(self, info : interface.Interaction):
        pass

    def track(self, pre : interface.Particle, post : interface.Particle):
        pass

# Patch the interface to use the newly defined class and run tests (True).
interface.patch(MyInterface, True)

