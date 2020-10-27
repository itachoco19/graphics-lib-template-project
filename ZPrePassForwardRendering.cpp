#include "ZPrePassForwardRendering.hpp"





ZPrePassForwardRendering::ZPrePassForwardRendering(const std::string& name, const DepthPass& zPass, std::shared_ptr<ForwardRenderingRenderPipeline> forwardRenderingRenderPipeline)
	: RenderPipelineWithImGuiComponents(name),
	  m_zPass(zPass),
	  m_forwardRenderingRenderPipeline(forwardRenderingRenderPipeline)
{
	m_zPass.initializeDepthStencilBuffer(m_forwardRenderingRenderPipeline->getDepthStencilBuffer());
}

void ZPrePassForwardRendering::render(const cg::Scene& scene)
{
	m_forwardRenderingRenderPipeline->getRenderTarget()->refresh();
	m_forwardRenderingRenderPipeline->getDepthStencilBuffer()->refresh();

	m_zPass.render(scene);
	m_forwardRenderingRenderPipeline->render(scene);
}

void ZPrePassForwardRendering::render()
{
}

void ZPrePassForwardRendering::drawImGuiComponents()
{
	m_zPass.drawImGuiComponents();
	m_forwardRenderingRenderPipeline->drawImGuiComponents();
}

