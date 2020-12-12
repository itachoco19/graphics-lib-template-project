#include "DepthPass.hpp"

DepthPass::DepthPass(const std::string& name, const DepthRenderPipelineList& zRenderPipelineList, std::shared_ptr<cg::IDepthStencilBuffer> depthStencilBuffer)
	: RenderPipelineWithImGuiComponents(name),
	  m_depthStencilBuffer(depthStencilBuffer),
	  m_zRenderPipelineList(zRenderPipelineList)
{
	for (auto zRenderPipeline : m_zRenderPipelineList)
	{
		zRenderPipeline->initializeDepthStencilBuffer(depthStencilBuffer);
	}
}

void DepthPass::render(const cg::Scene& scene, cg::Camera& customCamera)
{
	m_depthStencilBuffer->refresh();
	for (auto zRenderPipeline : m_zRenderPipelineList)
	{
		zRenderPipeline->render(scene, customCamera);
	}
}

void DepthPass::render(const cg::Scene& scene)
{
	m_depthStencilBuffer->refresh();
	for (auto zRenderPipeline : m_zRenderPipelineList)
	{
		zRenderPipeline->render(scene);
	}
}

void DepthPass::render()
{
	m_depthStencilBuffer->refresh();
	for (auto zRenderPipeline : m_zRenderPipelineList)
	{
		zRenderPipeline->render();
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