#include "DepthRenderPipeline.hpp"





DepthRenderPipeline::DepthRenderPipeline(const std::string& name, const TargetRenderingGroupNameList& targetRenderingGroupNameList, std::shared_ptr<cg::TransformConstantBuffer> transformConstantBuffer, const cg::RasterizationBasedRenderPipeline::ShaderDict& shaderDict, AdditionalSetCallScene additionalSetCall)
	: DepthRenderPipeline(name, targetRenderingGroupNameList, transformConstantBuffer, cg::API::shared.graphics()->createDepthStencilTester(cg::ComparisonFunction::less, cg::ComparisonFunction::always, true, false, true), shaderDict, additionalSetCall)
{
}

DepthRenderPipeline::DepthRenderPipeline(const std::string& name, const TargetRenderingGroupNameList& targetRenderingGroupNameList, std::shared_ptr<cg::TransformConstantBuffer> transformConstantBuffer, std::shared_ptr<cg::IDepthStencilTester> depthTesterLessFunction, const cg::RasterizationBasedRenderPipeline::ShaderDict& shaderDict, AdditionalSetCallScene additionalSetCall)
	: RenderPipelineSRTWithImGuiComponents(name, targetRenderingGroupNameList, cg::MainRenderTarget::shared.get(), nullptr, nullptr, transformConstantBuffer, nullptr, depthTesterLessFunction, shaderDict),
	  m_additionalSetCall(additionalSetCall)
{
}

void DepthRenderPipeline::initializeDepthStencilBuffer(std::shared_ptr<cg::IDepthStencilBuffer> depthStencilBuffer)
{
	m_depthStencilBuffer = depthStencilBuffer;
}

void DepthRenderPipeline::render(const cg::Scene& scene, const cg::Camera& customCamera)
{
	renderDefault(scene, customCamera, [&](const cg::Scene&){ m_renderTarget->set(m_depthStencilBuffer); m_additionalSetCall(scene); }, [](){}, true);
}

void DepthRenderPipeline::render(const cg::Scene& scene)
{
	renderDefault(scene, scene.camera, true);
}

void DepthRenderPipeline::render()
{
}

void DepthRenderPipeline::drawImGuiComponents()
{
	const auto depthTexture = m_depthStencilBuffer->getDepthBufferTexture();
	const auto textureSize = depthTexture->getSize();
	const auto aspect = textureSize.y/textureSize.x;
	const auto displayingSize = cpp::Vector2D<float>(1.0, aspect)*500.0;
	ImGui::ImageDepth(m_depthStencilBuffer, { displayingSize.x, displayingSize.y });
}
