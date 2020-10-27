#pragma once
#include "CameraController.hpp"





namespace ImGui
{
	bool CameraJumpButton(CameraController& cameraController, cg::Camera& camera, const cg::Transform& target);
}