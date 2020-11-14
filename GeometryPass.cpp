#include "GeometryPass.hpp"

GeometryPass::GeometryPass(const std::string& name, const GeometryRenderPipelineList& geometryRenderPipelineList)
	: RenderPipelineWithImGuiComponents(name),
	  m_geometryRenderPipelineList(geometryRenderPipelineList)
{
}

void GeometryPass::render(const cg::Scene& scene, cg::Camera& customCamera)
{
	for (auto geometryRenderPipeline : m_geometryRenderPipelineList)
	{
		geometryRenderPipeline->render(scene, customCamera);
	}
}

void GeometryPass::render(const cg::Scene& scene)
{
	for (auto geometryRenderPipeline : m_geometryRenderPipelineList)
	{
		geometryRenderPipeline->render(scene);
	}
}

void GeometryPass::render()
{

	for (auto geometryRenderPipeline : m_geometryRenderPipelineList)
	{
		geometryRenderPipeline->render();
	}
}

cg::GBuffer GeometryPass::getGBuffer() const
{
	if (m_geometryRenderPipelineList.empty())
	{
		return cg::GBuffer();
	}
	return m_geometryRenderPipelineList.begin()->get()->getGBuffer();
}

void GeometryPass::initializeMultipleRenderTarget(std::shared_ptr<cg::IMultipleRenderTarget> multipleRenderTarget)
{
	for (auto geometryRenderPipeline : m_geometryRenderPipelineList) 
	{
		geometryRenderPipeline->initializeMultipleRenderTarget(multipleRenderTarget);
	}
}

void GeometryPass::initializeDepthStencilBuffer(std::shared_ptr<cg::IDepthStencilBuffer> depthStencilBuffer)
{
	for (auto geometryRenderPipeline : m_geometryRenderPipelineList)
	{
		geometryRenderPipeline->initializeDepthStencilBuffer(depthStencilBuffer);
	}
}

void GeometryPass::drawImGuiComponents()
{
	for (auto geometryRenderPipeline : m_geometryRenderPipelineList)
	{
		if (ImGui::TreeNode(geometryRenderPipeline->name().c_str()))
		{
			geometryRenderPipeline->drawImGuiComponents();

			ImGui::TreePop();
		}
	}
}
