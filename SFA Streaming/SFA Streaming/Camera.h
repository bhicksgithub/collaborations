#pragma once
#include <Windows.h>
#include <exception>
#include <string>

namespace VNCCamera {
	class CameraException : public std::exception
	{
	public:
		char *issue;
		CameraException(char *reason) {
			issue = reason;
		}
		virtual const char* what() const throw()
		{
			std::string reason = "Camera exception occured: ";
			std::string iss(issue);
			std::string msg = reason + iss;
			const char *cMsg = msg.c_str();
			rsize_t sz = strlen(cMsg) + 1;
			char *retMsg = new char[sz];
			retMsg[strlen(cMsg) - 1] = 0;
			strcpy_s(retMsg, sz, cMsg);

			return retMsg;
		}
	};
}

struct ROI {
	unsigned short sx;
	unsigned short sy;
	unsigned short ex;
	unsigned short ey;
};

class Camera
{
public:

	unsigned short WX, WY;

	virtual array<unsigned char> ^ getFrame() = 0;

	virtual unsigned short * getRawFrame() = 0;

	virtual ~Camera() {};

	char * getName() {
		return name;
	}

	virtual void setROI(unsigned short startX, unsigned short startY,
		unsigned short endX, unsigned short endY) {
		region.sx = startX;
		region.sy = startY;
		region.ex = endX;
		region.ey = endY;
	}

	virtual void setExposureTime(unsigned int e) {
		expTime = e;
	}

protected:

	char *name;

	unsigned int expTime;

	unsigned int gain;

	ROI region;

};