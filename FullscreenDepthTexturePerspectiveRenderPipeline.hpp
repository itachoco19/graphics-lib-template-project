#pragma once
#include "FullscreenTextureRenderPipeline.hpp"
#include "ShaderConstant.hpp"





class FullscreenDepthTexturePerspectiveRenderPipeline
	: public FullscreenTextureRenderPipeline
{
private:
	class DepthLinearizerConstant
		: public cg::Constant
	{
	public:
		DepthLinearizerConstant();

		void update(float nearZ, float farZ);
	};
	DepthLinearizerConstant m_constant;
	std::shared_ptr<cg::IDynamicConstantBuffer> m_constantBuffer;
public:
	FullscreenDepthTexturePerspectiveRenderPipeline(const std::string& name, std::shared_ptr<cg::IDepthStencilBuffer> target, std::shared_ptr<cg::ITextureSampler> targetSampler);
	FullscreenDepthTexturePerspectiveRenderPipeline(const std::string& name, std::shared_ptr<cg::IDepthStencilBuffer> target, std::shared_ptr<cg::ITextureSampler> targetSampler, std::shared_ptr<cg::IRenderTarget> renderTarget, const FullscreenQuad& quad);

	void changeTarget(std::shared_ptr<cg::IDepthStencilBuffer> target);

	void render(const cg::Projection& projection);
};