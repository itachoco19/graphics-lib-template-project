#pragma once
#include <GraphicsLib.hpp>





namespace ImGui
{
	class DrawableObjectMaterialInspector
	{
	private:
		ImGui::SearchBar m_searchBar;

		std::string m_previewShaderStage;
	public:
		void draw(const cg::DrawableObject& object);

		void reset();
	};
}
