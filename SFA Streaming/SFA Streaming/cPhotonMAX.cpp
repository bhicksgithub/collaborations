#include "cPhotonMAX.h"

using namespace VNCCamera;

cPhotonMAX::cPhotonMAX(uns32 expTime, int16 gain,
	uns16 roiXStart, uns16 roiXEnd,
	uns16 roiYStart, uns16 roiYEnd) {
	
	region = { roiXStart, roiXEnd, 1, roiYStart, roiYEnd, 1 };
	this->WX = (roiXEnd - roiXStart) + 1;
	this->WY = (roiYEnd - roiYStart) + 1;
	this->expTime = expTime;

	started = false;

	char cam_name[CAM_NAME_LEN];
	
	rs_bool success = true;
	success &= pl_pvcam_init();
	success &= pl_cam_get_name(0, cam_name);
	success &= pl_cam_open(cam_name, &hCam, OPEN_EXCLUSIVE);

	if (!success && pl_error_code() != 0) {
		CameraException e("camera connection error");
		throw e;
	}

	camMutex = CreateMutex(
		NULL,
		FALSE,
		NULL
	);

	startStream();
}

cPhotonMAX::~cPhotonMAX() {
	/* Finish the sequence */
	pl_exp_finish_seq(hCam, frame, 0);

	/*Uninit the sequence */
	pl_exp_uninit_seq();
	free(frame);

	pl_cam_close(hCam);
	pl_pvcam_uninit();
}

void cPhotonMAX::setROI(unsigned short startX, unsigned short startY,
	unsigned short endX, unsigned short endY) {
	
	WaitForSingleObject(camMutex, INFINITE);
	region = { startX, endX, 1, startY, endY, 1 };
	this->WX = (endX - startX) + 1;
	this->WY = (endY - startY) + 1;
	ReleaseMutex(camMutex);
	refreshCameraSettings();
}

void cPhotonMAX::setGain(unsigned short g) {
	uns16 gain = g;
	WaitForSingleObject(camMutex, INFINITE);
	//refreshCameraSettings();
	pl_set_param(hCam, PARAM_GAIN_MULT_FACTOR, (void *)&gain);
	ReleaseMutex(camMutex);
	startIfNot();
}

void cPhotonMAX::startIfNot() {
	// TODO: Find a way to synchronize this.

	WaitForSingleObject(camMutex, INFINITE);
	if (!started) {
		pl_exp_start_seq(hCam, frame);
		started = true;
	}
	ReleaseMutex(camMutex);
}

void cPhotonMAX::refreshCameraSettings() {
	// TODO: use a mutex here.
	WaitForSingleObject(camMutex, INFINITE);
	pl_exp_finish_seq(hCam, frame, 0);
	pl_exp_setup_seq(hCam, 1, 1, &region, TIMED_MODE, expTime, &size);
	started = false;
	ReleaseMutex(camMutex);
}

array<unsigned char> ^ cPhotonMAX::getFrame() {
	int16 status;
	uns32 not_needed;

	startIfNot();

	WaitForSingleObject(camMutex, INFINITE);
	/* wait for data or error */
	while (pl_exp_check_status(hCam, &status, &not_needed) &&
		(status != READOUT_COMPLETE && status != READOUT_FAILED));
	/* Check Error Codes */
	if (status == READOUT_FAILED) {
		CameraException e("data collection error");
		throw e;
	}
	
	uns32 sz = this->WX * this->WY;
	array<unsigned char> ^pdata = gcnew array<unsigned char>(sz * 3);
	for (uns32 i = 0; i < sz; i++) {
		uns16 pixel = frame[i];
		unsigned char upper = pixel >> 8;

		pdata[3 * i + 0] = upper;
		pdata[3 * i + 1] = upper;
		pdata[3 * i + 2] = upper;
	}
	ReleaseMutex(camMutex);
	refreshCameraSettings();

	return pdata;
}

unsigned short * cPhotonMAX::getRawFrame() {
	int16 status;
	uns32 not_needed;

	startIfNot();
		
	WaitForSingleObject(camMutex, INFINITE);
	/* wait for data or error */
	while (pl_exp_check_status(hCam, &status, &not_needed) &&
		(status != READOUT_COMPLETE && status != READOUT_FAILED));
	/* Check Error Codes */
	if (status == READOUT_FAILED) {
		CameraException e("data collection error");
		throw e;
	}

	unsigned short * rawFrame = new unsigned short[size / sizeof(uns16)];
	for (uns32 i = 0; i < size / sizeof(uns16); i++) {
		rawFrame[i] = frame[i];
	}
	ReleaseMutex(camMutex);
	refreshCameraSettings();

	return rawFrame;
}

void cPhotonMAX::setExposureTime(unsigned int e) {
	this->expTime = e;
	refreshCameraSettings();
}

void cPhotonMAX::startStream() {
	/* Init a sequence set the region, exposure mode and exposure time */
	rs_bool success = true;
	
	success &= pl_exp_init_seq();
	success &= pl_exp_setup_seq(hCam, 1, 1, &region, TIMED_MODE, 100, &size);
	frame = (uns16*)malloc(size);

	if (!success && pl_error_code() != 0) {
		CameraException e("camera connection error");
		throw e;
	}
}