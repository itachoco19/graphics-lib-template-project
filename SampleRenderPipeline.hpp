#pragma once
#include "SampleShadingRenderPipeline.hpp"
#include "ForwardRenderingRenderPipeline.hpp"
#include "DepthPass.hpp"





class SampleRenderPipeline
	: public ForwardRenderingRenderPipeline
{
private:
	std::shared_ptr<cg::IDepthStencilBuffer> m_shadowMap;
	std::shared_ptr<cg::ITextureSampler> m_shadowMapSampler;

	SampleShadingRenderPipeline m_shadingRenderPipeline;
	DepthPass m_shadowMapRenderingPass;	

	bool m_shouldRefreshRenderTarget;
	bool m_shouldRefreshDepthStencilBuffer;
public:
	static const std::string targetRenderingGroupName;
public:
	SampleRenderPipeline(std::shared_ptr<cg::IRenderTarget> renderTarget, std::shared_ptr<cg::IDepthStencilBuffer> depthStencilBuffer, std::shared_ptr<cg::IDepthStencilTester> depthStencilTester, bool shouldRefreshRenderTarget = true, bool shouldRefreshDepthStencilBuffer = true);
	virtual ~SampleRenderPipeline() = default;

	void render(const cg::Scene& scene) override;
	void render() override;

	void drawImGuiComponents() override;
};
