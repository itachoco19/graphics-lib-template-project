#pragma once
#include <GraphicsLib.hpp>
#include "CameraController.hpp"





namespace ImGui
{
	class CameraInspector
	{
	public:
		void draw(cg::Camera& camera, CameraController& cameraController);
		void reset();
	};
}
