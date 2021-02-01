
class Particle:
    """Python wrapper for the CParticle class in COAST.

    Attributes
    ----------
    time : float
        Time of the CORSIKA particle event in seconds.
    position : list
        x, y, z values of the particle position in meters.
    atmosphericDepth : float
        Travel depth in g/cm^2 for the particle.
    energy : float
        Current total energy of the particle.
    weight : float
        TODO: unknown
    particleID : int
        Particle type as integer ID in CORSIKA convention.
    hadronicGeneration : int
        TODO: unknown
    """

    def __init__(self, t, x, y, z, depth, energy, weight, ID, hadgen):
        """Construct particle info.

        Parameters
        ----------
        t : float
            Time of the CORSIKA particle event in seconds.
        x, y, z : float
            Position of the interaction in meters.
        depth : float
            Atmospheric travel depth in g/cm^2.
        energy : float
            Current total energy of the particle.
        weight : float
            TODO: unknown
        ID : int
            Particle type as integer ID in CORSIKA convention.
        hadgen : int
            TODO: unknown
        """

        self.time = t
        self.position = [x, y, z]
        self.atmosphericDepth = depth
        self.energy = energy
        self.weight = weight
        self.particleID = ID
        self.hadronicGeneration = hadgen

