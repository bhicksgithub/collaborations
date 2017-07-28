from astropy.io import fits
import numpy as np
import matplotlib.pyplot as plt

filepath = "darks/E1G0#"
imdata = []
for i in range(1, 21):
	fp = filepath + str(i) + ".fits"
	hdulist = fits.open(fp)
	data = hdulist[0].data
	imdata.append(data)

avframe = np.mean(imdata, axis=0)
stdframe = np.std(imdata, axis=0)
mean = avframe[0][0]
stdev = stdframe[0][0]
print("Mean: {0}\nSigma: {1}\n".format(mean, stdev))

plt.imshow(stdframe)
plt.show()