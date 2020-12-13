#include "RenderPipelineMRTWithImGuiComponents.hpp"





RenderPipelineMRTWithImGuiComponents::RenderPipelineMRTWithImGuiComponents(const std::string& name, const TargetRenderingGroupNameList& targetRenderingGroupNameList, std::shared_ptr<cg::IMultipleRenderTargets> mrt, std::shared_ptr<cg::IDepthStencilBuffer> depthStencilBuffer, std::shared_ptr<cg::IDepthStencilTester> depthStencilTester, std::shared_ptr<cg::IRasterizer> rasterizer, std::shared_ptr<cg::IAlphaBlender> alphaBlender, const ShaderDict& shaders, std::shared_ptr<cg::MaterialConstantBuffer> materialConstantBuffer, std::shared_ptr<cg::TransformConstantBuffer> transformConstantBuffer, std::shared_ptr<cg::LightConstantBuffer> lightConstantBuffer) noexcept
	: RenderPipelineMRT(name, targetRenderingGroupNameList, mrt, depthStencilBuffer, depthStencilTester, rasterizer, alphaBlender, shaders, materialConstantBuffer, transformConstantBuffer, lightConstantBuffer)
{
}
