#pragma once
#include "DefferedRenderPipeline.hpp"
#include "FullscreenTextureRenderPipeline.hpp"
#include "FullscreenDepthTextureRenderPipeline.hpp"
#include "DepthPass.hpp"





class DefferedSampleRenderPipeline
	: public DefferedRenderPipeline
{
private:
	std::shared_ptr<cg::IDepthStencilBuffer> m_shadowMap;
	DepthPass m_shadowMapRenderingPass;
public:
	static const std::string targetRenderingGroupName;
private:
	DefferedSampleRenderPipeline(std::shared_ptr<cg::IRenderTarget> lightingPassRenderTarget, const GeometryPass& geometryPass, std::shared_ptr<cg::ITextureSampler> gbufferSampler, std::shared_ptr<cg::IDepthStencilBuffer> shadowMap);
	DefferedSampleRenderPipeline(std::shared_ptr<cg::IRenderTarget> lightingPassRenderTarget, std::shared_ptr<cg::IMultipleRenderTarget> geometryPassMRT, std::shared_ptr<cg::IDepthStencilBuffer> geometryPassDepthStencilBuffer, std::shared_ptr<cg::ITextureSampler> gbufferSampler, std::shared_ptr<cg::IDepthStencilBuffer> shadowMap);
public:
	DefferedSampleRenderPipeline(std::shared_ptr<cg::IRenderTarget> lightingPassRenderTarget);
	DefferedSampleRenderPipeline(std::shared_ptr<cg::IRenderTarget> lightingPassRenderTarget, std::shared_ptr<cg::ITextureSampler> gbufferSampler);
	virtual ~DefferedSampleRenderPipeline() = default;

	void render(const cg::Scene& scene) override;
	void render() override;
	
	void drawImGuiComponents() override;
};
