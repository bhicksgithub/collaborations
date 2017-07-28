from astropy.io import fits
import numpy as np
import matplotlib.pyplot as plt

filepath = "flats/E50G0#"
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
mask = []
for j in avframe:
	row = []
	for k in j:
		if abs(k - mean) > 5*stdev:
			# Dead pixel
			row.append(0)
		else:
			row.append(1)
		histdata.append(k)
	
	mask.append(row)

flatframe = np.divide(avframe, np.max(avframe))#np.subtract(avframe, mean)
plt.imshow(flatframe, cmap='gray')
plt.show()

plt.hist(histdata)
plt.show()
plt.imshow(mask, cmap='gray')
plt.show()