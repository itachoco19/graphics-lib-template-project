#include "DefferedRenderingRenderPipeline.hpp"





DefferedRenderingRenderPipeline::DefferedRenderingRenderPipeline(const std::string& name, const GeometryPass& geometryPass, const LightingPass& lightingPass)
	: RenderPipelineWithImGuiComponents(name),
	  m_geometryPass(geometryPass),
	  m_lightingPass(lightingPass)
{
}

void DefferedRenderingRenderPipeline::render()
{
}

void DefferedRenderingRenderPipeline::render(const cg::Scene& scene)
{
	m_geometryPass.render(scene);
	m_lightingPass.setGBuffer(m_geometryPass.getGBuffer());
	m_lightingPass.render();
}





DefferedRenderingRenderPipeline::GeometryPass::GeometryPass(const std::string& name, const GeometryRenderPipelineList& geometryRenderPipelineList)
	: RenderPipelineWithImGuiComponents(name),
	m_geometryRenderPipelineList(geometryRenderPipelineList)
{
}

void DefferedRenderingRenderPipeline::GeometryPass::render(const cg::Scene& scene, cg::Camera& customCamera)
{
	for (auto geometryRenderPipeline : m_geometryRenderPipelineList)
	{
		geometryRenderPipeline->render(scene, customCamera);
	}
}

void DefferedRenderingRenderPipeline::GeometryPass::render(const cg::Scene& scene)
{
	for (auto geometryRenderPipeline : m_geometryRenderPipelineList)
	{
		geometryRenderPipeline->render(scene);
	}
}

void DefferedRenderingRenderPipeline::GeometryPass::render()
{

	for (auto geometryRenderPipeline : m_geometryRenderPipelineList)
	{
		geometryRenderPipeline->render();
	}
}

cg::GBuffer DefferedRenderingRenderPipeline::GeometryPass::getGBuffer() const
{
	if (m_geometryRenderPipelineList.empty())
	{
		return cg::GBuffer();
	}
	return m_geometryRenderPipelineList.begin()->get()->getGBuffer();
}

void DefferedRenderingRenderPipeline::GeometryPass::initializeMultipleRenderTarget(std::shared_ptr<cg::IMultipleRenderTarget> multipleRenderTarget)
{
	for (auto geometryRenderPipeline : m_geometryRenderPipelineList)
	{
		geometryRenderPipeline->initializeMultipleRenderTarget(multipleRenderTarget);
	}
}

void DefferedRenderingRenderPipeline::GeometryPass::initializeDepthStencilBuffer(std::shared_ptr<cg::IDepthStencilBuffer> depthStencilBuffer)
{
	for (auto geometryRenderPipeline : m_geometryRenderPipelineList)
	{
		geometryRenderPipeline->initializeDepthStencilBuffer(depthStencilBuffer);
	}
}

void DefferedRenderingRenderPipeline::GeometryPass::drawImGuiComponents()
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





cg::GBuffer DefferedRenderingRenderPipeline::LightingPass::acessToGBuffer() const
{
	return m_gbuffer;
}

DefferedRenderingRenderPipeline::LightingPass::LightingPass(const std::string& name, std::shared_ptr<cg::LightConstantBuffer> lightConstantBuffer, std::shared_ptr<cg::IPixelShader> pixelShader, const ShaderResourceSetCall& setCallPixelShaderResource)
	: FullscreenQuadRenderPipeline(name, lightConstantBuffer, pixelShader, setCallPixelShaderResource)
{
}

DefferedRenderingRenderPipeline::LightingPass::LightingPass(const std::string& name, std::shared_ptr<cg::IRenderTarget> renderTarget, std::shared_ptr<cg::LightConstantBuffer> lightConstantBuffer, std::shared_ptr<cg::IPixelShader> pixelShader, const ShaderResourceSetCall& setCallPixelShaderResource)
	: FullscreenQuadRenderPipeline(name, renderTarget, lightConstantBuffer, pixelShader, setCallPixelShaderResource)
{
}

DefferedRenderingRenderPipeline::LightingPass::LightingPass(const std::string& name, std::shared_ptr<cg::IRenderTarget> renderTarget, std::shared_ptr<cg::LightConstantBuffer> lightConstantBuffer, const FullscreenQuad& quad, std::shared_ptr<cg::IPixelShader> pixelShader, const ShaderResourceSetCall& setCallPixelShaderResource)
	: FullscreenQuadRenderPipeline(name, renderTarget, quad, lightConstantBuffer, pixelShader, setCallPixelShaderResource)
{
}

void DefferedRenderingRenderPipeline::LightingPass::setGBuffer(const cg::GBuffer& gbuffer)
{
	m_gbuffer = gbuffer;
}
