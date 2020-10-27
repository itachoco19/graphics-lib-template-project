#pragma once
#include "IImGuiComponentsHolder.hpp"
#include <GraphicsLib.hpp>





class SphereWithImGuiComponents
	: public cg::Sphere,
	  public IImGuiComponentsHolder
{
public:
	SphereWithImGuiComponents();
	SphereWithImGuiComponents(float radius);
	SphereWithImGuiComponents(float radiusX, float radiusY, float radiusZ);
	virtual ~SphereWithImGuiComponents() = default;

	void drawImGuiComponents() override;
};