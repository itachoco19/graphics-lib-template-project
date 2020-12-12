#include "ForwardZPrePassRenderPipeline.hpp"





ForwardZPrePassRenderPipeline::ForwardZPrePassRenderPipeline(const std::string& name, const DepthPass& zPass, std::shared_ptr<ForwardRenderPipeline> forwardRenderingRenderPipeline)
	: RenderPipelineWithImGuiComponents(name),
	  m_zPass(zPass),
	  m_forwardRenderingRenderPipeline(forwardRenderingRenderPipeline)
{
}

void ForwardZPrePassRenderPipeline::render(const cg::Scene& scene)
{
	m_zPass.render(scene);
	m_forwardRenderingRenderPipeline->render(scene);
}

void ForwardZPrePassRenderPipeline::render()
{
}

void ForwardZPrePassRenderPipeline::drawImGuiComponents()
{
	m_zPass.drawImGuiComponents();
	m_forwardRenderingRenderPipeline->drawImGuiComponents();
}

