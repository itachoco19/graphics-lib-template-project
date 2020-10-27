#include "PlaneWithImGuiComponents.hpp"
#include <GraphicsLib.hpp>





PlaneWithImGuiComponents::PlaneWithImGuiComponents()
{
}

PlaneWithImGuiComponents::PlaneWithImGuiComponents(float width, float height)
	: Plane(width, height)
{
}

void PlaneWithImGuiComponents::drawImGuiComponents()
{
	auto size = getSizeXY();
	if (ImGui::InputVector2D("Size", size))
	{
		changeSize(size);
	}
}
