#pragma once
#include "Camera.h"
#include <stdlib.h>
#include "master.h"
#include "pvcam.h"

class cPhotonMAX :
	public Camera
{
public:
	int16 hCam;

	cPhotonMAX(uns32 expTime, int16 gain,
		uns16 roiXStart, uns16 roiXEnd,
		uns16 roiYStart, uns16 roiYEnd);

	~cPhotonMAX();

	void setROI(unsigned short startX, unsigned short startY, unsigned short endX, unsigned short endY);

	void setGain(unsigned short g);

	array<unsigned char> ^ getFrame();

	unsigned short * getRawFrame();

	void setExposureTime(unsigned int e);

private:
	uns32 buffer_size, frame_size;
	uns16 *frame;
	uns32 size;
	rs_bool started;
	rgn_type region;
	HANDLE camMutex;

	void startStream();
	void startIfNot();
	void refreshCameraSettings();
};

