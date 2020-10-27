#include "FullscreenDepthTextureRenderPipeline.hpp"





FullscreenDepthTextureRenderPipeline::FullscreenDepthTextureRenderPipeline(const std::string& name, std::shared_ptr<cg::IDepthStencilBuffer> target)
	: FullscreenDepthTextureRenderPipeline(name, target, cg::API::shared.graphics()->createTextureSampler(), cg::MainRenderTarget::shared.get(), FullscreenQuad())
{
}

FullscreenDepthTextureRenderPipeline::FullscreenDepthTextureRenderPipeline(const std::string& name, std::shared_ptr<cg::IDepthStencilBuffer> target, std::shared_ptr<cg::ITextureSampler> targetSampler, std::shared_ptr<cg::IRenderTarget> renderTarget, const FullscreenQuad& quad)
	: RenderPipeline(name),
	  m_orthographicRenderPipeline(name, target, targetSampler, renderTarget, quad),
	  m_perspectiveRenderPipeline(name, target, targetSampler, renderTarget, quad)
{
}

void FullscreenDepthTextureRenderPipeline::changeTarget(std::shared_ptr<cg::IDepthStencilBuffer> target)
{
	m_orthographicRenderPipeline.changeTarget(target);
	m_perspectiveRenderPipeline.changeTarget(target);
}

void FullscreenDepthTextureRenderPipeline::render()
{
}

void FullscreenDepthTextureRenderPipeline::render(const cg::Scene& scene)
{
}

void FullscreenDepthTextureRenderPipeline::render(const cg::Projection& projection)
{
	if (projection.getType() == cg::ProjectionType::perspective)
	{
		m_perspectiveRenderPipeline.render(projection);
	}
	else
	{
		m_orthographicRenderPipeline.render();
	}
}
