#include "DepthPass.hpp"

DepthPass::DepthPass(const std::string& name, const DepthRenderPipelineList& zRenderPipelineList)
	: RenderPipelineWithImGuiComponents(name),
	  m_zRenderPipelineList(zRenderPipelineList)
{
}

void DepthPass::render(const cg::Scene& scene, cg::Camera& customCamera)
{
	for (auto zRenderPipeline : m_zRenderPipelineList)
	{
		zRenderPipeline->render(scene, customCamera);
	}
}

void DepthPass::render(const cg::Scene& scene)
{
	for (auto zRenderPipeline : m_zRenderPipelineList)
	{
		zRenderPipeline->render(scene);
	}
}

void DepthPass::render()
{
	for (auto zRenderPipeline : m_zRenderPipelineList)
	{
		zRenderPipeline->render();
	}
}

void DepthPass::initializeDepthStencilBuffer(std::shared_ptr<cg::IDepthStencilBuffer> depthStencilBuffer)
{
	for (auto zRenderPipeline : m_zRenderPipelineList)
	{
		zRenderPipeline->initializeDepthStencilBuffer(depthStencilBuffer);
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