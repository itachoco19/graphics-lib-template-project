#pragma once
#include "IImGuiComponentsHolder.hpp"

#include <GraphicsLib.hpp>





class ShapeWithImGuiComponents
	: public cg::Shape,
	  public IImGuiComponentsHolder
{
public:
	ShapeWithImGuiComponents(const cpp::Vector3D<float>& size);
	virtual ~ShapeWithImGuiComponents() = default;
};
