#pragma once
#include "IImGuiComponentsHolder.hpp"
#include <GraphicsLib.hpp>





class RenderPipelineWithImGuiComponents
	: public cg::RenderPipeline,
	  public IImGuiComponentsHolder
{
public:
	RenderPipelineWithImGuiComponents(const std::string& name) noexcept;
	virtual ~RenderPipelineWithImGuiComponents() = default;
};