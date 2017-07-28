from astropy.io import fits
import numpy as np
import matplotlib.pyplot as plt

exposures = [1, 25, 50, 75, 100, 200, 500, 1000, 2000]
y1 = []
y2 = []

for t in exposures:
    file = "E{0}G0#".format(t)
    filepath = "darks/" + file
    imdata = []
    for i in range(1, 21):
        fp = filepath + str(i) + ".fits"
        hdulist = fits.open(fp)
        data = hdulist[0].data
        imdata.append(data)
	
    avframe = np.mean(imdata)
    meanrms = np.mean(list(map((lambda x: np.std(x)), imdata)))
    y2.append(100*meanrms / avframe)
    noise = np.sqrt(sum(np.std(i)**2 for i in imdata))
    y1.append(100*noise / avframe)

#plt.scatter(exposures, y1, label="Square root of squared rms", marker='x')
plt.scatter(exposures, y2, label="Mean of rms")
#plt.show()

plt.title("RMS vs Exposure Time")
plt.xlabel("Exposure Time (msec)")
plt.ylabel("RMS")
#plt.legend(loc='upper right')
plt.show()