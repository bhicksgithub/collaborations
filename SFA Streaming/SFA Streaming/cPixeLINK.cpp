#include "cPixeLINK.h"
#include <PixeLINKApi.h>
#include <PixeLINKCodes.h>
#include <PixeLINKTypes.h>


cPixeLINK::cPixeLINK(unsigned short wx, unsigned short wy)
{
	ReturnCode rc = Api::Initialize(0, hCamera);
	if (!Api::IsSuccess(rc)) {
		System::Windows::Forms::MessageBox::Show("Unable to initialize a camera.");
		return;
	}

	array<float> ^exp = gcnew array<float>(1);
	exp[0] = 1/1000;
	FeatureFlags flags = FeatureFlags::Manual;
	Api::SetFeature(hCamera, Feature::Shutter, flags, 1, exp);

	this->WX = wx;
	this->WY = wy;
	bSize = getBufferSize();

	InitializeCriticalSectionAndSpinCount(&camCS, 0x00000400);
}


cPixeLINK::~cPixeLINK()
{
	Api::Uninitialize(hCamera);
	DeleteCriticalSection(&camCS);
}

array<unsigned char>^ cPixeLINK::getFrame()
{
	EnterCriticalSection(&camCS);
	ReturnCode rc = Api::SetStreamState(hCamera, StreamState::Start);
	handleReturnCode(rc);
	FrameDescriptor fDesc;
	
	array<unsigned char> ^tempFrame = gcnew array<unsigned char>(bSize);
	rc = Api::GetNextFrame(hCamera, bSize, tempFrame, fDesc);
	handleReturnCode(rc);

	int oSize;
	Api::FormatImage(tempFrame, fDesc, ImageFormat::RawRgb24, nullptr, oSize);
	array<unsigned char> ^ret = gcnew array<unsigned char>(oSize);
	rc = Api::FormatImage(tempFrame, fDesc, ImageFormat::RawRgb24, ret, oSize);
	handleReturnCode(rc);

	rc = Api::SetStreamState(hCamera, StreamState::Stop);
	handleReturnCode(rc);
	LeaveCriticalSection(&camCS);

	return ret;
}

unsigned short * cPixeLINK::getRawFrame()
{
	EnterCriticalSection(&camCS);
	ReturnCode rc = Api::SetStreamState(hCamera, StreamState::Start);
	handleReturnCode(rc);
	FrameDescriptor fDesc;

	array<short> ^tempFrame = gcnew array<short>(bSize);
	rc = Api::GetNextFrame16(hCamera, bSize, tempFrame, fDesc);
	handleReturnCode(rc);

	unsigned short *retFrame = new unsigned short[bSize];
	for (unsigned int i = 0; i < bSize; i++) {
		short pixel = tempFrame[i];

		// Convert from big endian to little.
		short correctValue = ((pixel & 0xFF00) >> 8) | ((pixel & 0x00FF) << 8);
		retFrame[i] = correctValue;
	}

	rc = Api::SetStreamState(hCamera, StreamState::Stop);
	handleReturnCode(rc);
	LeaveCriticalSection(&camCS);

	return retFrame;
}

void cPixeLINK::setExposureTime(unsigned int e)
{
	EnterCriticalSection(&camCS);
	FeatureFlags flags = FeatureFlags::Manual;
	array<float> ^parm = gcnew array<float>(1);
	float exp = (float)(e / 1000000.0);
	parm[0] = exp;
	ReturnCode rc = Api::SetFeature(hCamera, Feature::Shutter, flags, 1, parm);
	handleReturnCode(rc);
	LeaveCriticalSection(&camCS);
}

void cPixeLINK::setGain(float g)
{
	EnterCriticalSection(&camCS);
	FeatureFlags flags = FeatureFlags::Manual;
	array<float> ^parm = gcnew array<float>(1);
	parm[0] = g;
	ReturnCode rc = Api::SetFeature(hCamera, Feature::Gain, flags, 1, parm);
	handleReturnCode(rc);
	LeaveCriticalSection(&camCS);
}

/*
 * Most of this was stolen directly from the getsnapshot example.
 * Many of the function calls had to be updated, but the general
 * idea is still there.
 *
 * Query the camera for region of interest(ROI), decimation, and pixel format.
 * Using this information, we can calculate the size of a raw image.
 *
 * Returns 0 on failure.
 */
unsigned int cPixeLINK::getBufferSize() {
	array <float> ^parms = gcnew array <float>(4);
	unsigned short roiWidth;
	unsigned short roiHeight;
	unsigned int decimation;		// integral factor by which the image is reduced
	unsigned int pixelFormat;
	unsigned int numPixels;
	unsigned int pixelSize;
	FeatureFlags flags = FeatureFlags::Manual;
	int numParams;

	ReturnCode rc;

	/*
	// Get region of interest (ROI)
	numParams = 4; // left, top, width, height
	rc = Api::GetFeature(hCamera, Feature::Roi, flags, numParams, parms);
	handleReturnCode(rc);
	roiWidth = (unsigned int)parms[2];
	roiHeight = (unsigned int)parms[3];
	WX = roiWidth;
	WY = roiHeight;
	*/

	// Set ROI (and resolution).
	numParams = 4;
	roiWidth = WX;
	roiHeight = WY;
	parms[0] = 0;
	parms[1] = 0;
	parms[2] = roiWidth;
	parms[3] = roiHeight;
	Api::SetFeature(hCamera, Feature::Roi, flags, numParams, parms);

	// Set decimation to 1x1. Eg: no decimation.
	numParams = 2;
	parms[0] = 1;
	parms[1] = 0;
	Api::SetFeature(hCamera, Feature::Decimation, flags, numParams, parms);

	// Query decimation
	numParams = 2; // decimation value, decimation type (e.g. bin, average, ...)
	rc = Api::GetFeature(hCamera, Feature::Decimation, flags, numParams, parms);
	handleReturnCode(rc);
	decimation = (unsigned int)parms[0];

	// We can calulate the number of pixels now.
	numPixels = (roiWidth / decimation) * (roiHeight / decimation);

	// Knowing pixel format means we can determine how many bytes per pixel.
	numParams = 1;
	rc = Api::GetFeature(hCamera, Feature::PixelFormat, flags, numParams, parms);
	handleReturnCode(rc);
	pixelFormat = (unsigned int)parms[0];

	// And now the size of the frame
	pixelSize = getPixelSize(pixelFormat);

	return numPixels * pixelSize;
}

/*
 * Given the pixel format, return the size of a individual pixel (in bytes)
 *
 * Returns 0 on failure.
 */
unsigned int cPixeLINK::getPixelSize(unsigned int pixelFormat)
{
	unsigned int retVal = 0;

	switch (pixelFormat) {

	case PIXEL_FORMAT_MONO8:
	case PIXEL_FORMAT_BAYER8_GRBG:
	case PIXEL_FORMAT_BAYER8_RGGB:
	case PIXEL_FORMAT_BAYER8_GBRG:
	case PIXEL_FORMAT_BAYER8_BGGR:
		retVal = 1;
		break;

	case PIXEL_FORMAT_YUV422:
	case PIXEL_FORMAT_MONO16:
	case PIXEL_FORMAT_BAYER16_GRBG:
	case PIXEL_FORMAT_BAYER16_RGGB:
	case PIXEL_FORMAT_BAYER16_GBRG:
	case PIXEL_FORMAT_BAYER16_BGGR:
		retVal = 2;
		break;

	case PIXEL_FORMAT_RGB24:
		retVal = 3;
		break;

	case PIXEL_FORMAT_RGB48:
		retVal = 6;
		break;

	default:
		break;
	}

	return retVal;
}

void cPixeLINK::handleReturnCode(ReturnCode rc) {
	if (!Api::IsSuccess(rc)) {
		CameraException ^e = gcnew CameraException(rc);
		throw e;
	}
}