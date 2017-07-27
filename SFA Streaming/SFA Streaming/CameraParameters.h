#pragma once
#include "CameraPreview.h"
#include "Camera.h"

namespace VNCTest {
	ref class CameraParameters
	{
	public:
		CameraPreview ^prev;
		Camera *cam;

		CameraParameters(CameraPreview ^preview, Camera *camera)
		{
			prev = preview;
			cam = camera;
		}

		~CameraParameters()
		{
			delete prev;
		}
	};
}
