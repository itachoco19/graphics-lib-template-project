#include "SphereWithImGuiComponents.hpp"
#include <GraphicsLib.hpp>





SphereWithImGuiComponents::SphereWithImGuiComponents()
{
}

SphereWithImGuiComponents::SphereWithImGuiComponents(float radius)
	: Sphere(radius)
{
}

SphereWithImGuiComponents::SphereWithImGuiComponents(float radiusX, float radiusY, float radiusZ)
	: Sphere(radiusX, radiusY, radiusZ)
{
}

void SphereWithImGuiComponents::drawImGuiComponents()
{
	auto radius = getRadius();
	if (ImGui::InputVector3D("Radius", radius))
	{
		changeRadius(radius);
	}
}
