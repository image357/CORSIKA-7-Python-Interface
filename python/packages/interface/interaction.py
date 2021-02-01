
class Interaction:
    """Python wrapper for the CInteraction class in COAST.

    Attributes
    ----------
    position : list
        x, y, z values of the interaction position in meters.
    labEnergy : float
        Total energy in the laboritory frame.
    crossSection : float
        Cross section of the particle interaction.
    elasticity : float
        Elasticity of the interaction.
    projectileID : int
        Numeric CORSIKA ID of the incident particle.
    targetID : int
        Numeric CORSIKA ID of the target particle.
    """

    def __init__(self, x, y, z, etot, sigma, kela, pID, tID):
        """Construct interaction info.

        Parameters
        ----------
        x, y, z : float
            Position of the interaction in meters.
        etot : float
            Total energy in the laboritory frame.
        sigma : float
            Cross section of the interaction.
        kela : float
            Elasticity of the interaction.
        pID : int
            Projectile CORSIKA ID.
        tID : int
            Target CORSIKA ID.
        """

        self.position = [x, y, z]
        self.labEnergy = etot
        self.crossSection = sigma
        self.elasticity = kela
        self.projectileID = pID
        self.targetID = tID

