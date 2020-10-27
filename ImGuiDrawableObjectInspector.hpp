#pragma once
#include "ImGuiDrawableObjectMaterialInspector.hpp"
#include <GraphicsLib.hpp>





namespace ImGui
{
	class DrawableObjectInspector
	{
	private:
		ImGui::DrawableObjectMaterialInspector m_materialInspector;
	public:
		void draw(cg::DrawableObject& object);

		void reset();
	};
}
