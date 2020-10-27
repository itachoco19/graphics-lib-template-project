#pragma once
#include "IImGuiComponentsHolder.hpp"
#include <GraphicsLib.hpp>





class PlaneWithImGuiComponents
	: public cg::Plane,
	  public IImGuiComponentsHolder
{
public:
	PlaneWithImGuiComponents();
	PlaneWithImGuiComponents(float width, float height);
	virtual ~PlaneWithImGuiComponents() = default;

	void drawImGuiComponents() override;
};