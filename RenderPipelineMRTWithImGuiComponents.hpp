#pragma once
#include "IImGuiComponentsHolder.hpp"
#include <GraphicsLib.hpp>





class RenderPipelineMRTWithImGuiComponents
	: public cg::RenderPipelineMRT,
	  public IImGuiComponentsHolder
{
public:
	RenderPipelineMRTWithImGuiComponents(const std::string& name, const TargetRenderingGroupNameList& targetRenderingGroupNameList, std::shared_ptr<cg::IMultipleRenderTarget> mrt, std::shared_ptr<cg::IDepthStencilBuffer> depthStencilBuffer, std::shared_ptr<cg::MaterialConstantBuffer> materialConstantBuffer, std::shared_ptr<cg::TransformConstantBuffer> transformConstantBuffer, std::shared_ptr<cg::LightConstantBuffer> lightConstantBuffer, std::shared_ptr<cg::IDepthStencilTester> depthStencilTester, const ShaderDict& shaders) noexcept;
	virtual ~RenderPipelineMRTWithImGuiComponents() = default;
};