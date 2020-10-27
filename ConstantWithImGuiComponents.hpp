#pragma once
#include "IImGuiComponentsHolder.hpp"

#include <GraphicsLib.hpp>





class ConstantWithImGuiComponents
	: public cg::Constant,
	  public IImGuiComponentsHolder
{
public:
	ConstantWithImGuiComponents();
	template <typename T>
	ConstantWithImGuiComponents(std::shared_ptr<T> pData)
		: Constant(pData)
	{
	}
	virtual ~ConstantWithImGuiComponents() = default;
};