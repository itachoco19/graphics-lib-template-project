#pragma once
#include "FullscreenTextureRenderPipeline.hpp"
#include "ShaderConstant.hpp"





class FullscreenDepthTextureOrthographicRenderPipeline
	: public FullscreenTextureRenderPipeline
{
public:
	FullscreenDepthTextureOrthographicRenderPipeline(const std::string& name, std::shared_ptr<cg::IDepthStencilBuffer> target, std::shared_ptr<cg::ITextureSampler> targetSampler);
	FullscreenDepthTextureOrthographicRenderPipeline(const std::string& name, std::shared_ptr<cg::IDepthStencilBuffer> target, std::shared_ptr<cg::ITextureSampler> targetSampler, std::shared_ptr<cg::IRenderTarget> renderTarget, const FullscreenQuad& quad);

	void changeTarget(std::shared_ptr<cg::IDepthStencilBuffer> target);
	
	void render();
};