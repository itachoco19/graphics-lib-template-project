#pragma once
#include "DepthRenderPipeline.hpp"
#include "DepthPass.hpp"
#include "ForwardRenderPipeline.hpp"





class ForwardZPrePassRenderPipeline
	: public RenderPipelineWithImGuiComponents
{
private:
	DepthPass m_zPass;
	std::shared_ptr<ForwardRenderPipeline> m_forwardRenderingRenderPipeline;
public:
	ForwardZPrePassRenderPipeline(const std::string& name, const DepthPass& zPass, std::shared_ptr<ForwardRenderPipeline> forwardRenderingRenderPipeline);
	virtual ~ForwardZPrePassRenderPipeline() = default;

	void render(const cg::Scene& scene) override;
	void render() override;

	void drawImGuiComponents() override;
};