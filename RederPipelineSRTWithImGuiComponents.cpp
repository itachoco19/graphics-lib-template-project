#include "RenderPipelineSRTWithImGuiComponents.hpp"





RenderPipelineSRTWithImGuiComponents::RenderPipelineSRTWithImGuiComponents(const std::string& name, const TargetRenderingGroupNameList& targetRenderingGroupNameList, std::shared_ptr<cg::IRenderTarget> renderTarget, std::shared_ptr<cg::IDepthStencilBuffer> depthStencilBuffer, std::shared_ptr<cg::MaterialConstantBuffer> materialConstantBuffer, std::shared_ptr<cg::TransformConstantBuffer> transformConstantBuffer, std::shared_ptr<cg::LightConstantBuffer> lightConstantBuffer, std::shared_ptr<cg::IDepthStencilTester> depthStencilTester, const ShaderDict& shaders) noexcept
	: RenderPipelineSRT(name, targetRenderingGroupNameList, renderTarget, depthStencilBuffer,  materialConstantBuffer, transformConstantBuffer, lightConstantBuffer, depthStencilTester, shaders)
{
}
