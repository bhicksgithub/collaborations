#pragma once
#include "Camera.h"
#include "Windows.h"

using namespace PixeLINK;

class cPixeLINK :
	public Camera
{
public:
	cPixeLINK(unsigned short wx, unsigned short wy);
	~cPixeLINK();
	array<unsigned char> ^ getFrame();
	unsigned short * getRawFrame();
	void setExposureTime(unsigned int e);
	void setGain(float g);

private:
	int hCamera;
	unsigned int bSize;
	CRITICAL_SECTION camCS;

	unsigned int getBufferSize();
	unsigned int getPixelSize(unsigned int pixelFormat);
	void handleReturnCode(ReturnCode rc);
};

