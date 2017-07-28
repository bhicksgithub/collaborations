from astropy.io import fits
import numpy as np
import matplotlib.pyplot as plt

files = ["E25G0#", "E50G0#", "E75G0#", "E100G0#", "E200G0#", "E500G0#", "E1000G0#", "E2000G0#"]
x = [25, 50, 75, 100, 200, 500, 1000, 2000]
y = []

for file in files:
	filepath = "darks/" + file
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
			if abs(k - mean) > 3*stdev:
				histdata.append(k)
	
	m = np.mean(histdata)
	y.append(m)

plt.scatter(x, y)
plt.show()