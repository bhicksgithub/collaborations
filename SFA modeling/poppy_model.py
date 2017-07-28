import poppy
import matplotlib.pyplot as plt
import numpy as np
from fringepattern import FringePattern

# Wavelength in meters
wavelength = 632.8e-9
# Pupil diameter in meters
d = 0.01 * (125 / 150)
# Pupil radius
r = d / 2
# Image plane dimensions
# Effective focal length in mm
f = 300
# Detector size in pixels
det_size_p = 512
# Detector physical size in mm
det_size_mm = 12.4
# FOV in arcseconds (small angle approx. used)
RTOAS = (180 / np.pi) * 3600
alpha = (det_size_mm / f) * RTOAS
# Pixel scale in "/pixel
ps = alpha / det_size_p
# The FOV parameter is half the detector size in pixels.
fov_p = det_size_p / 2

def get_num_segments(M):
    # N = 3M(M-1)+1
    N = 3*M*(M-1)+1
    return N

ideal_osys = poppy.OpticalSystem()
dm_osys = poppy.OpticalSystem()
ca = poppy.CircularAperture(radius=r)
fp = FringePattern(radius=r, m=8)

# Create DM mirror layout
n_rings = 7
mirror_segments = np.array(range(0,get_num_segments(n_rings)))
mirror_segments = np.append(mirror_segments, np.array(range(128,169)))
mirror_segments = np.setdiff1d(mirror_segments, mirror_segments[[133,140,147,154,161]])

gap = 5e-5
aperture_eff = 7.7e-3
flatsize = (aperture_eff-(n_rings-1)*2*gap)/(n_rings*2-1)
ha = poppy.MultiHexagonAperture(rings=n_rings, flattoflat=flatsize,
        gap=5e-5, center=True, segmentlist=mirror_segments)

ideal_sfa = poppy.CompoundAnalyticOptic( opticslist=[ca, fp], name='Ideal SFA optics')
dm_sfa = poppy.CompoundAnalyticOptic( opticslist=[ca, ha, fp], name='SFA optics w/DM')
dm_osys.add_pupil(dm_sfa)
dm_osys.add_detector(pixelscale=ps, fov_pixels=fov_p)
ideal_osys.add_pupil(ideal_sfa)
ideal_osys.add_detector(pixelscale=ps, fov_pixels=fov_p)

#wf = osys.input_wavefront(wavelength)

dm_osys.display(colorbar_orientation='vertical')
plt.show()
ideal_osys.display(colorbar_orientation='vertical')
plt.show()

ideal_psf = ideal_osys.calc_psf(wavelength)
dm_psf = dm_osys.calc_psf(wavelength)
#dm_psf.writeto("psf.fits")
poppy.display_PSF(dm_psf, title='PSF w/DM')
plt.show()
poppy.display_PSF(ideal_psf, title='Ideal PSF')
plt.show()

print(np.max(dm_psf[0].data)/np.max(ideal_psf[0].data))
print(np.sum(dm_psf[0].data))
print(np.sum(ideal_psf[0].data))
#plt.imshow(psf[0].data, cmap='gray')