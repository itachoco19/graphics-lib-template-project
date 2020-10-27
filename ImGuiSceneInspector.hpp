#pragma once
#include "ImGuiSceneDrawableObjectInspector.hpp"
#include "ImGuiSceneLightInspector.hpp"
#include "ImGuiCameraInspector.hpp"

#include <GraphicsLib.hpp>





namespace ImGui
{
	class SceneInspector
	{
	private:
		SceneDrawableObjectInspector m_objectInspector;
		SceneLightInspector m_lightInspector;
		CameraInspector m_cameraInspector;
	public:
		void draw(cg::Scene& scene, CameraController& cameraController);

		void reset();
	};
}