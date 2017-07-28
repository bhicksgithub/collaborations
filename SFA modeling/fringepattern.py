import poppy
import numpy as np
import astropy.units as u

from poppy.poppy_core import OpticalElement, Wavefront, PlaneType, _PUPIL, _IMAGE, _RADIANStoARCSEC

class FringePattern(poppy.AnalyticOpticalElement):
    """ Defines an interference pattern

    Parameters
    ----------
    name : string
        Descriptive name
    radius : float
        Radius of the pupil, in meters. Default is 1.0
	m : int
		Number of fringes per pupil diameter. Default is 1
    """

    @poppy.utils.quantity_input(radius=u.meter)
    def __init__(self, name=None, radius=1.0*u.meter, m=1, planetype=PlaneType.unspecified, **kwargs):

        if name is None:
            name = "Fringe pattern, radius={}, m={}".format(radius, m)
        super(FringePattern, self).__init__(name=name, planetype=planetype, **kwargs)
        self.radius=radius
        self.m=m
        # for creating input wavefronts - let's pad a bit:
        self.pupil_diam = 2 * self.radius

    def get_transmission(self, wave):
        """ Compute the transmission of the fringe pattern.
        """
        if not isinstance(wave, Wavefront):  # pragma: no cover
            raise ValueError("FringePattern get_transmission must be called with a Wavefront "
                             "to define the spacing")
        assert (wave.planetype != _IMAGE)

        #y, x = self.get_coordinates(wave)
        x = np.zeros(wave.shape, dtype=np.complex_)
        y = np.zeros(wave.shape, dtype=np.complex_)
        sz = wave.shape[0]
        c = sz / 2
        phase_dist = self.m/sz
        pi = np.pi
		
        for a in range(sz):
            for b in range(sz):
                dist = c-b
                phi = 2*pi*dist*phase_dist
                I = np.sin(phi)
                R = np.cos(phi)
                x[a,b] = complex(1, 0)
                y[a,b] = complex(R, I)

        z = np.abs(x+y)**2
        z /= np.max(z)
        self.transmission = z
        return self.transmission