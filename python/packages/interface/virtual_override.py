from abc import ABC, abstractmethod
from .interaction import Interaction
from .particle import Particle
from .cppwrapper import disableWrite, disableInteraction, disableTrack

class Override(ABC):
    """Abstract interface class that has to be overridden.

    Inherit from this class in order to override the interface default
    behavior.

    Abstract methods
    ----------------
    init(self) :
        called in COAST inida_()

    close(self) :
        called in COAST cloda_()

    write(self, subblock) :
        called in COAST wrida_()
        subblock is of type bytes
        length is determined by CORSIKA thinning option

    interaction(self, info) :
        called in COAST interaction_()
        info is of type Interaction

    track(self, pre, post) :
        called in COAST track_()
        pre and post are of type Particle
    """

    def __init__(self):
        """Construct default virutal interface."""
        pass


    @abstractmethod
    def init(self):
        """Initialize interface."""
        pass


    @abstractmethod
    def close(self):
        """Finalize interface."""
        pass


    @abstractmethod
    def write(self, subblock: bytes):
        """Write CORSIKA subblock.
        
        Parameters
        ----------
        subblock : bytes
            CORSIKA DataSubBlock of size 39*8*4 bytes (thinning) or
            39*7*4 bytes (no thinning)
        """
        pass


    @abstractmethod
    def interaction(self, info: Interaction):
        """Retrieve interaction info.

        Parameters
        ----------
        info : Interaction
            Contains all interaction info provided to the COAST interface
        """
        pass


    @abstractmethod
    def track(self, pre: Particle, post: Particle):
        """Retrieve particle track info.

        Parameters
        ----------
        pre : Particle
            Pre-track particle info provided by COAST
        post : Particle
            Post-track particle info provided by COAST
        """
        pass


class DefaultOverride(Override):
    """Default implementation of the abstract Override class."""

    def __init__(self):
        """Construct class."""
        pass

    def init(self):
        """Do nothing."""
        pass

    def close(self):
        """Do nothing."""
        pass

    def write(self, subblock : bytes):
        """Disable further calls to write().

        Uses the cppwrapper module to prevent COAST from calling python write()
        methods.
        
        Parameters
        ----------
        subblock : bytes
            unsued
        """
        disableWrite()
        pass

    def interaction(self, info : Interaction):
        """Disable further calls to interaction().

        Uses the cppwrapper module to prevent COAST from calling python
        interaction() methods.

        Parameters
        ----------
        info : Interaction
            unused
        """
        disableInteraction()
        pass

    def track(self, pre : Particle, post : Particle):
        """Disable further calls to track().

        Uses the cppwrapper module to prevent COAST from calling python track()
        methods.

        Parameters
        ----------
        pre : Particle
            unused
        post : Particle
            unused
        """
        disableTrack()
        pass

