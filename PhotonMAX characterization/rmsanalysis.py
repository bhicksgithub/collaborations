from astropy.io import fits
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.mlab as mlab
from scipy.stats import norm

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
plt.imshow(bias, cmap='gray')
plt.show()

(mu, sigma) = norm.fit(bias)
n, b, p = plt.hist(bias.flatten(), normed=True, label="Bias data")
fit_range = np.linspace(np.min(bias), np.max(bias), 100)
gaussian_text = "$\mu=${:0.2f}, $\sigma=${:0.2f}".format(mu, sigma)
g = plt.plot(fit_range, mlab.normpdf(fit_range, mu, sigma), 'r--',
            label=gaussian_text)
plt.legend(handles=g)
plt.title("Histogram of Pixel Values in Bias Frame")
plt.xlabel("Value (ADU)")
plt.ylabel("Probability")
plt.show()

exposures = [25, 50, 75, 100, 200, 500, 1000, 2000]
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

plt.scatter(exposures, rms, label="Mean of rms", marker='.')
plt.title("Mean RMS vs Exposure Time")
plt.xlabel("Exposure Time (msec)")
plt.ylabel("Mean RMS (ADU)")
plt.show()