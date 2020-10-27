#pragma once
#include "FullscreenDepthTextureOrthographicRenderPipeline.hpp"
#include "FullscreenDepthTexturePerspectiveRenderPipeline.hpp"





class FullscreenDepthTextureRenderPipeline
	: public cg::RenderPipeline
{
private:
	FullscreenDepthTextureOrthographicRenderPipeline m_orthographicRenderPipeline;
	FullscreenDepthTexturePerspectiveRenderPipeline m_perspectiveRenderPipeline;
public:
	FullscreenDepthTextureRenderPipeline(const std::string& name, std::shared_ptr<cg::IDepthStencilBuffer> target);
	FullscreenDepthTextureRenderPipeline(const std::string& name, std::shared_ptr<cg::IDepthStencilBuffer> target, std::shared_ptr<cg::ITextureSampler> targetSampler, std::shared_ptr<cg::IRenderTarget> renderTarget, const FullscreenQuad& quad);

	virtual ~FullscreenDepthTextureRenderPipeline() = default;



	void changeTarget(std::shared_ptr<cg::IDepthStencilBuffer> target);



	void render() override;
	void render(const cg::Scene& scene) override;
	void render(const cg::Projection& projection);
};