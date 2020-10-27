#include "BoxWithImGuiComponents.hpp"
#include <GraphicsLib.hpp>





BoxWithImGuiComponents::BoxWithImGuiComponents()
{
}

BoxWithImGuiComponents::BoxWithImGuiComponents(float width, float height, float depth)
	: Box(width, height, depth)
{
}

void BoxWithImGuiComponents::drawImGuiComponents()
{
	auto size = getSize();
	if (ImGui::InputVector3D("Size", size))
	{
		changeSize(size);
	}
}
