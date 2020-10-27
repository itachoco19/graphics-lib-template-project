#pragma once
#include "DepthRenderPipeline.hpp"
#include "DepthPass.hpp"
#include "ForwardRenderingRenderPipeline.hpp"





class ZPrePassForwardRendering
	: public RenderPipelineWithImGuiComponents
{
private:
	DepthPass m_zPass;
	std::shared_ptr<ForwardRenderingRenderPipeline> m_forwardRenderingRenderPipeline;
public:
	ZPrePassForwardRendering(const std::string& name, const DepthPass& zPass, std::shared_ptr<ForwardRenderingRenderPipeline> forwardRenderingRenderPipeline);
	virtual ~ZPrePassForwardRendering() = default;

	void render(const cg::Scene& scene) override;
	void render() override;

	void drawImGuiComponents() override;
};