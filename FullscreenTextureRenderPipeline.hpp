#pragma once
#include "FullscreenQuadRenderPipeline.hpp"



class FullscreenTextureRenderPipeline
	: public FullscreenQuadRenderPipeline
{
private:
	std::shared_ptr<cg::ITexture2D> m_target;
	std::shared_ptr<cg::ITextureSampler> m_targetSampler;
public:
	FullscreenTextureRenderPipeline(const std::string& name, std::shared_ptr<cg::ITexture2D> target, std::shared_ptr<cg::ITextureSampler> targetSampler);
	FullscreenTextureRenderPipeline(const std::string& name, std::shared_ptr<cg::ITexture2D> target, std::shared_ptr<cg::ITextureSampler> targetSampler, std::shared_ptr<cg::IRenderTarget> renderTarget, const FullscreenQuad& quad);
	
	FullscreenTextureRenderPipeline(const std::string& name, std::shared_ptr<cg::ITexture2D> target, std::shared_ptr<cg::ITextureSampler> targetSampler, std::shared_ptr<cg::IPixelShader> customPixelShader, AdditionalSetCall additionalSetCall = []() {});
	FullscreenTextureRenderPipeline(const std::string& name, std::shared_ptr<cg::ITexture2D> target, std::shared_ptr<cg::ITextureSampler> targetSampler,  std::shared_ptr<cg::IRenderTarget> renderTarget, const FullscreenQuad& quad, std::shared_ptr<cg::IPixelShader> customPixelShader, AdditionalSetCall additionalSetCall = [](){});



	void changeTarget(std::shared_ptr<cg::ITexture2D> target);
};