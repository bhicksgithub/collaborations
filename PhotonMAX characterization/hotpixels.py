from astropy.io import fits
import numpy as np
import matplotlib.pyplot as plt

filepath = "darks/E50G0#"
imdata = []
for i in range(1, 21):
	fp = filepath + str(i) + ".fits"
	hdulist = fits.open(fp)
	data = hdulist[0].data
	imdata.append(data)

avframe = np.mean(imdata, axis=0)
mean = np.mean(avframe)
stdev = np.std(avframe)
print("Mean: {0}\nSigma: {1}\n".format(mean, stdev))

histdata = []
for j in avframe:
	for k in j:
		#if abs(k - mean) > 10*stdev:
		#	print("Bad pixel")
		histdata.append(k)
			
plt.hist(histdata)
plt.show()