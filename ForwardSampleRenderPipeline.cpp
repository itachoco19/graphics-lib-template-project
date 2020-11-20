#include "ForwardSampleRenderPipeline.hpp"
#include "SimpleDirectionalLight.hpp"





const std::string ForwardSampleRenderPipeline::targetRenderingGroupName = "Sample";
const cg::RasterizationBasedRenderPipeline::TargetRenderingGroupNameList targetRenderingGroupNameList = { ForwardSampleRenderPipeline::targetRenderingGroupName };





ForwardSampleRenderPipeline::ForwardSampleRenderPipeline(std::shared_ptr<cg::IRenderTarget> renderTarget, std::shared_ptr<cg::IDepthStencilBuffer> depthStencilBuffer, std::shared_ptr<cg::IDepthStencilTester> depthStencilTester, bool shouldRefreshRenderTarget, bool shouldRefreshDepthStencilBuffer)
	: ForwardRenderPipeline("Test Render Pipeline", renderTarget, depthStencilBuffer),
	  m_shadowMap(cg::API::shared.graphics()->createDepthStencilBuffer(cg::System::getWindowInfo().getSize(), cg::TextureFormat::D32_FLOAT, renderTarget->getMSAASampleCount(), renderTarget->getMSAAQualityLevel())),
	  m_shadowMapSampler(cg::API::shared.graphics()->createTextureSampler([]() 
      {
	      cg::TextureSamplerDescriptor descriptor;
		  descriptor.filter = cg::TextureFilter::trilinear;
		  return descriptor;
	  }())),
	  m_shadowMapRenderingPass(DepthPass("Shadow Map Render Pipeline", { std::make_shared<Position3Normal3DepthRenderPipeline>(targetRenderingGroupNameList) })),
	  m_shadingRenderPipeline(targetRenderingGroupNameList, renderTarget, depthStencilBuffer, depthStencilTester, m_shadowMap, m_shadowMapSampler),
	  m_shouldRefreshRenderTarget(shouldRefreshRenderTarget),
	  m_shouldRefreshDepthStencilBuffer(shouldRefreshDepthStencilBuffer)
{
	m_shadowMapRenderingPass.initializeDepthStencilBuffer(m_shadowMap);
}

ForwardSampleRenderPipeline::ForwardSampleRenderPipeline(std::shared_ptr<cg::IRenderTarget> renderTarget)
	: ForwardSampleRenderPipeline(renderTarget, cg::API::shared.graphics()->createDepthStencilTester(cg::ComparisonFunction::greater, cg::ComparisonFunction::always, true, false, true))
{
}

ForwardSampleRenderPipeline::ForwardSampleRenderPipeline(std::shared_ptr<cg::IRenderTarget> renderTarget, std::shared_ptr<cg::IDepthStencilTester> depthStencilTester, bool shouldRefreshRenderTarget, bool shouldRefreshDepthStencilBuffer)
	: ForwardSampleRenderPipeline(renderTarget, cg::API::shared.graphics()->createDepthStencilBuffer(cg::System::getWindowInfo().getSize(), cg::TextureFormat::D32_FLOAT), depthStencilTester, true, true)
{
}

void ForwardSampleRenderPipeline::render(const cg::Scene& scene)
{
	if (m_shouldRefreshRenderTarget)
	{
		getRenderTarget()->refresh();
	}
	if (m_shouldRefreshDepthStencilBuffer)
	{
		getDepthStencilBuffer()->refresh();
	}
	m_shadowMap->refresh();

	const auto keyLight = std::dynamic_pointer_cast<SimpleDirectionalLight>(scene.getLightDict().at("Key"));
	m_shadowMapRenderingPass.render(scene, keyLight->perspective);

	m_shadingRenderPipeline.render(scene);
}

void ForwardSampleRenderPipeline::render()
{
}

void ForwardSampleRenderPipeline::drawImGuiComponents()
{
}
