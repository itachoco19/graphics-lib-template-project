#include "SampleRenderPipeline.hpp"
#include "SimpleDirectionalLight.hpp"





const std::string SampleRenderPipeline::targetRenderingGroupName = "SimpleShading";
const cg::RasterizationBasedRenderPipeline::TargetRenderingGroupNameList targetRenderingGroupNameList = { SampleRenderPipeline::targetRenderingGroupName };





SampleRenderPipeline::SampleRenderPipeline(std::shared_ptr<cg::IRenderTarget> renderTarget, std::shared_ptr<cg::IDepthStencilBuffer> depthStencilBuffer, std::shared_ptr<cg::IDepthStencilTester> depthStencilTester, bool shouldRefreshRenderTarget, bool shouldRefreshDepthStencilBuffer)
	: ForwardRenderingRenderPipeline("Test Render Pipeline", renderTarget, depthStencilBuffer),
	  m_shadowMap(cg::API::shared.graphics()->createDepthStencilBuffer(1500, 800, cg::TextureFormat::D32_FLOAT, renderTarget->getMSAASampleCount(), renderTarget->getMSAAQualityLevel())),
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

void SampleRenderPipeline::render(const cg::Scene& scene)
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

void SampleRenderPipeline::render()
{
}

void SampleRenderPipeline::drawImGuiComponents()
{
}
