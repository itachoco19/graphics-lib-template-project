#pragma once
#include "IImGuiComponentsHolder.hpp"
#include <GraphicsLib.hpp>





class BoxWithImGuiComponents
	: public cg::Box,
	  public IImGuiComponentsHolder
{
public:
	BoxWithImGuiComponents();
	BoxWithImGuiComponents(float width, float height, float depth);
	virtual ~BoxWithImGuiComponents() = default;

	void drawImGuiComponents() override;
};
