#pragma once
#include "ImGuiSceneInspector.hpp"
#include "CameraController.hpp"
#include "RenderPipelineWithImGuiComponents.hpp"





namespace ImGui
{
	class GraphicsLibDefaultInspector
	{
	private:
		ImGui::SceneInspector m_sceneInspector;
	public:
		void draw(cg::Scene& scene, CameraController& cameraController, std::shared_ptr<RenderPipelineWithImGuiComponents> renderPipeline);
	};
}