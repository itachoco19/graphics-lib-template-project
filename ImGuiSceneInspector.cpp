#include "ImGuiSceneInspector.hpp"
#include "ImGuiProjectionInspector.hpp"
#include "ImGuiDrawableObjectInspector.hpp"
#include "IImGuiComponentsHolder.hpp"
#include <GraphicsLib.hpp>





namespace ImGui
{
	void SceneInspector::draw(cg::Scene& scene, CameraController& cameraController)
	{
		if (ImGui::TreeNode("Camera"))
		{
			m_cameraInspector.draw(scene.camera, cameraController);

			ImGui::TreePop();
		}

		if (ImGui::TreeNode("Light"))
		{
			m_lightInspector.draw(scene);

			ImGui::TreePop();
		}

		if (ImGui::TreeNode("Object"))
		{
			m_objectInspector.draw(scene, cameraController);

			ImGui::TreePop();
		}
	}
	void SceneInspector::reset()
	{
		m_objectInspector.reset();
		m_lightInspector.reset();
		m_cameraInspector.reset();
	}
}