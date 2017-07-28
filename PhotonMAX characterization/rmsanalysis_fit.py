from astropy.io import fits
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.mlab as mlab
from scipy.stats import norm, linregress

# Get a bias frame
file = "E1G0#"
filepath = "darks/" + file
bias_frames = []
for i in range(1, 21):
    fp = filepath + str(i) + ".fits"
    hdulist = fits.open(fp)
    data = hdulist[0].data
    bias_frames.append(data)

# Using the average of individual
# bias frames as master bias frame
bias = np.mean(bias_frames, axis=0)

exposures = [500, 1000, 2000]
rms = []

for t in exposures:
    file = "E{0}G0#".format(t)
    filepath = "darks/" + file
    imdata = []
    for i in range(1, 21):
        fp = filepath + str(i) + ".fits"
        hdulist = fits.open(fp)
        data = np.abs(hdulist[0].data - bias)
        imdata.append(data)
	
    avframe = np.mean(imdata, axis=0)
    meanrms = np.mean(list(map((lambda x: np.std(x)), imdata)))
    rms.append(meanrms)

m, y0, r, p, err = linregress(exposures, rms)
print("Slope = {0}, intercept = {1}".format(m, y0))
def y(x): return np.add(np.multiply(m,x), y0)

plt.scatter(exposures, rms, label="Mean of rms", marker='.')
plt.plot(exposures, y(exposures), 'r--')
plt.title("Mean RMS vs Exposure Time")
plt.xlabel("Exposure Time (msec)")
plt.ylabel("Mean RMS (ADU)")
plt.show()