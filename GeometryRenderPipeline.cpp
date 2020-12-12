#include "GeometryRenderPipeline.hpp"





GeometryRenderPipeline::GeometryRenderPipeline(const std::string& name, std::shared_ptr<cg::IMultipleRenderTargets> mrt, std::shared_ptr<cg::IDepthStencilBuffer> depthStencilBuffer, const TargetRenderingGroupNameList& targetRenderingGroupNameList, std::shared_ptr<cg::MaterialConstantBuffer> materialConstantBuffer, std::shared_ptr<cg::TransformConstantBuffer> transformConstantBuffer, const cg::RasterizationBasedRenderPipeline::ShaderDict& shaderDict, AdditionalSetCallScene additionalSetCall)
	: GeometryRenderPipeline(name, mrt, depthStencilBuffer, targetRenderingGroupNameList, materialConstantBuffer, transformConstantBuffer, cg::API::shared.graphics()->createDepthStencilTester(cg::ComparisonFunction::less, cg::ComparisonFunction::always, true, false, true), shaderDict, additionalSetCall)
{
}

GeometryRenderPipeline::GeometryRenderPipeline(const std::string& name, std::shared_ptr<cg::IMultipleRenderTargets> mrt, std::shared_ptr<cg::IDepthStencilBuffer> depthStencilBuffer, const TargetRenderingGroupNameList& targetRenderingGroupNameList, std::shared_ptr<cg::MaterialConstantBuffer> materialConstantBuffer, std::shared_ptr<cg::TransformConstantBuffer> transformConstantBuffer, std::shared_ptr<cg::IDepthStencilTester> depthTesterLessFunction, const cg::RasterizationBasedRenderPipeline::ShaderDict& shaderDict, AdditionalSetCallScene additionalSetCall)
	: RenderPipelineMRTWithImGuiComponents(name, targetRenderingGroupNameList, mrt, depthStencilBuffer, materialConstantBuffer, transformConstantBuffer, nullptr, depthTesterLessFunction, shaderDict),
	  m_additionalSetCall(additionalSetCall)
{
}

void GeometryRenderPipeline::render(const cg::Scene& scene, const cg::Camera& customCamera)
{
	m_multipleRenderTargets->refreshAll();
	m_depthStencilBuffer->refresh();

	renderDefault(scene, customCamera, true, [&](const cg::Scene&) { m_multipleRenderTargets->set(m_depthStencilBuffer); m_additionalSetCall(scene); }, []() {});
}

void GeometryRenderPipeline::render(const cg::Scene& scene)
{
	render(scene, scene.camera);
}

void GeometryRenderPipeline::render()
{

}

void GeometryRenderPipeline::drawImGuiComponents()
{
}
