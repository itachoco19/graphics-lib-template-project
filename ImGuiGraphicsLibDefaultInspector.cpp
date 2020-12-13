#include "ImGuiGraphicsLibDefaultInspector.hpp"





namespace ImGui
{
	void GraphicsLibDefaultInspector::draw(cg::Scene& scene, CameraController& cameraController, std::shared_ptr<RenderPipelineWithImGuiComponents> renderPipeline)
	{
		const auto windowSize = cg::System::getWindowInfo().getSize();
		ImGui::SetNextWindowSize(ImVec2(static_cast<float>(windowSize.x)*0.3f, static_cast<float>(windowSize.y)), ImGuiCond_Once);
		ImGui::SetNextWindowPos(ImVec2(0.0, 0.0));
		ImGui::SetNextWindowSizeConstraints(ImVec2(0.0f, static_cast<float>(windowSize.y)), ImVec2(static_cast<float>(windowSize.x), static_cast<float>(windowSize.y)));


		ImGui::Begin("Inspector", 0, ImGuiWindowFlags_NoMove);

		if (ImGui::TreeNode("Scene"))
		{
			m_sceneInspector.draw(scene, cameraController);

			ImGui::TreePop();
		}
		if (ImGui::TreeNode("Render Pipeline"))
		{
			if (renderPipeline)
			{
				renderPipeline->drawImGuiComponents();
			}

			ImGui::TreePop();
		}

		ImGui::End();
	}
}
