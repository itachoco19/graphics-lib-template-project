#pragma once
#include <GraphicsLib.hpp>





namespace ImGui
{
	class SceneLightInspector
	{
	private:
		ImGui::SearchBar m_searchBar;
	public:
		void draw(const cg::Scene& scene);

		void reset();
	};
}
