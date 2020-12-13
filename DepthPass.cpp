#include "DepthPass.hpp"

DepthPass::DepthPass(const std::string& name, const DepthRenderPipelineList& zRenderPipelineList, std::shared_ptr<cg::IDepthStencilBuffer> depthStencilBuffer, bool shouldResolveDepthStencilBuffer)
	: RenderPipelineWithImGuiComponents(name),
	  m_depthStencilBuffer(depthStencilBuffer),
	  m_zRenderPipelineList(zRenderPipelineList),
	  m_shouldResolveDepthStencilBuffer(shouldResolveDepthStencilBuffer)
{
}

void DepthPass::render(const cg::Scene& scene, cg::Camera& customCamera)
{
	m_depthStencilBuffer->refresh();
	for (auto zRenderPipeline : m_zRenderPipelineList)
	{
		zRenderPipeline->render(scene, customCamera);
	}
	if (m_shouldResolveDepthStencilBuffer)
	{
		m_depthStencilBuffer->getDepthBufferTexture()->resolve();
	}
}

void DepthPass::render(const cg::Scene& scene)
{
	m_depthStencilBuffer->refresh();
	for (auto zRenderPipeline : m_zRenderPipelineList)
	{
		zRenderPipeline->render(scene);
	}
	if (m_shouldResolveDepthStencilBuffer)
	{
		m_depthStencilBuffer->getDepthBufferTexture()->resolve();
	}
}

void DepthPass::render()
{
	m_depthStencilBuffer->refresh();
	for (auto zRenderPipeline : m_zRenderPipelineList)
	{
		zRenderPipeline->render();
	}
	if (m_shouldResolveDepthStencilBuffer)
	{
		m_depthStencilBuffer->getDepthBufferTexture()->resolve();
	}
}

void DepthPass::drawImGuiComponents()
{
	for (auto zRenderPipeline : m_zRenderPipelineList)
	{
		if (ImGui::TreeNode(zRenderPipeline->name().c_str()))
		{
			zRenderPipeline->drawImGuiComponents();

			ImGui::TreePop();
		}
	}
}