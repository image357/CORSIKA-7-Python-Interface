from .virtual_override import Override, DefaultOverride
from .interaction import Interaction
from .particle import Particle

class CppAccess:
    """Intermediate class between user defined interface and C++ calls.

    This class acts as a mediator between the C++ and python part of the
    interface. The user defined init(), close(), write(), interaction()
    and track() methods are called from here in order to allow some pythonic
    level of abstraction between C++ calls and the interface.

    Attributes
    ----------
    _override : Override
        Stores the currently used python interface. By default it is
        initialized with DefaultOverride()
    """

    def __init__(self):
        """Construct class and set DefaultOverride as interface"""
        self._override = DefaultOverride()

    def patch(self, classtype, runtest=False, *args, **kwargs):
        """Set new interface class and run tests if neccessary.
        
        This method is called by the user if he wants to override the
        interface with a custom class.

        Parameters
        ----------
        classtype : class
            Class reference (not instance of it!) that will be used to
            create a new interface and override the current one.
        runtest : bool, optional
            Indicator to run unit tests on the new interface class. This
            is usefull when writing a new interface with override.py.
        *args, **kwargs : any, optional
            Unnamed and named arguments given to the constructor of the new
            interface class.
        """

        assert issubclass(classtype, Override)
        self._override = classtype(*args, **kwargs)

        if runtest:
            print("running interface tests")
            # TODO: implement interface tests
            pass

    def _init(self):
        """Call interface init()"""
        self._override.init()

    def _close(self):
        """Call interface close()"""
        self._override.close()

    def _write(self, subblock: bytes):
        """Call interface write()"""
        self._override.write(subblock)

    def _interaction(self, x, y, z, etot, sigma, kela, pID, tID):
        """Create Interaction instance and call interface interaction()"""
        info = Interaction(x, z, z, etot, sigma, kela, pID, tID)
        self._override.interaction(info)

    def _track(self,
            t_1, x_1, y_1, z_1, depth_1, energy_1, weight_1, ID_1, hadgen_1,
            t_2, x_2, y_2, z_2, depth_2, energy_2, weight_2, ID_2, hadgen_2):
        """Create Particle instances and call interface track()"""
        particle_1 = Particle(t_1, x_1, y_1, z_1, depth_1, energy_1, weight_1, ID_1, hadgen_1)
        particle_2 = Particle(t_2, x_2, y_2, z_2, depth_2, energy_2, weight_2, ID_2, hadgen_2)
        self._override.track(particle_1, particle_2)

