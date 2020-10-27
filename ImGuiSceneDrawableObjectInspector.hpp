#pragma once
#include "ImGuiDrawableObjectInspector.hpp"
#include "CameraController.hpp"

#include <GraphicsLib.hpp>





namespace ImGui
{
	class SceneDrawableObjectInspector
	{
	private:
		ImGui::SearchBar m_groupSearchBar;
		ImGui::SearchBar m_objectSearchBar;
		DrawableObjectInspector m_drawableObjectInspector;
	public:
		void draw(cg::Scene& scene, CameraController& cameraController);

		void reset();
	};
}
