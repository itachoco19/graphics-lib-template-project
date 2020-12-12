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
	  m_shadowMapRenderingPass(DepthPass("Shadow Map Render Pipeline", { std::make_shared<Position3Normal3DepthRenderPipeline>(targetRenderingGroupNameList) }, m_shadowMap)),
	  m_shadingRenderPipeline(targetRenderingGroupNameList, renderTarget, depthStencilBuffer, depthStencilTester, m_shadowMap, m_shadowMapSampler),
	  m_shouldRefreshRenderTarget(shouldRefreshRenderTarget),
	  m_shouldRefreshDepthStencilBuffer(shouldRefreshDepthStencilBuffer)
{
}

ForwardSampleRenderPipeline::ForwardSampleRenderPipeline(std::shared_ptr<cg::IRenderTarget> renderTarget)
	: ForwardSampleRenderPipeline(renderTarget, cg::API::shared.graphics()->createDepthStencilTester(cg::ComparisonFunction::less, cg::ComparisonFunction::always, true, false, true))
{
}

ForwardSampleRenderPipeline::ForwardSampleRenderPipeline(std::shared_ptr<cg::IRenderTarget> renderTarget, std::shared_ptr<cg::IDepthStencilTester> depthStencilTester, bool shouldRefreshRenderTarget, bool shouldRefreshDepthStencilBuffer)
	: ForwardSampleRenderPipeline(renderTarget, cg::API::shared.graphics()->createDepthStencilBuffer(renderTarget->getSize(), cg::TextureFormat::D32_FLOAT, renderTarget->getMSAASampleCount(), renderTarget->getMSAAQualityLevel()), depthStencilTester, shouldRefreshRenderTarget, shouldRefreshDepthStencilBuffer)
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

	const auto keyLight = scene.getLight<SimpleDirectionalLight>("Key");
	m_shadowMapRenderingPass.render(scene, keyLight->perspective);
	m_shadowMap->getDepthBufferTexture()->resolve();

	m_shadingRenderPipeline.render(scene);
}

void ForwardSampleRenderPipeline::render()
{
}

void ForwardSampleRenderPipeline::drawImGuiComponents()
{
}
