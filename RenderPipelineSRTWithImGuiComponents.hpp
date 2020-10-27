#pragma once
#include "IImGuiComponentsHolder.hpp"
#include <GraphicsLib.hpp>





class RenderPipelineSRTWithImGuiComponents
	: public cg::RenderPipelineSRT,
	  public IImGuiComponentsHolder
{
public:
	RenderPipelineSRTWithImGuiComponents(const std::string& name, const TargetRenderingGroupNameList& targetRenderingGroupNameList, std::shared_ptr<cg::IRenderTarget> renderTarget, std::shared_ptr<cg::IDepthStencilBuffer> depthStencilBuffer, std::shared_ptr<cg::MaterialConstantBuffer> materialConstantBuffer, std::shared_ptr<cg::TransformConstantBuffer> transformConstantBuffer, std::shared_ptr<cg::LightConstantBuffer> lightConstantBuffer, std::shared_ptr<cg::IDepthStencilTester> depthStencilTester, const ShaderDict& shaders) noexcept;
	virtual ~RenderPipelineSRTWithImGuiComponents() = default;
};