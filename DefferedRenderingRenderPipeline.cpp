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

DefferedRenderingRenderPipeline::LightingPass::LightingPass(const std::string& name, std::shared_ptr<cg::IPixelShader> pixelShader, const ShaderResourceSetCall& setCallPixelShaderResource)
	: FullscreenQuadRenderPipeline(name, pixelShader, setCallPixelShaderResource)
{
}

DefferedRenderingRenderPipeline::LightingPass::LightingPass(const std::string& name, std::shared_ptr<cg::IRenderTarget> renderTarget, std::shared_ptr<cg::IPixelShader> pixelShader, const ShaderResourceSetCall& setCallPixelShaderResource)
	: FullscreenQuadRenderPipeline(name, renderTarget, pixelShader, setCallPixelShaderResource)
{
}

DefferedRenderingRenderPipeline::LightingPass::LightingPass(const std::string& name, std::shared_ptr<cg::IRenderTarget> renderTarget, const FullscreenQuad& quad, std::shared_ptr<cg::IPixelShader> pixelShader, const ShaderResourceSetCall& setCallPixelShaderResource)
	: FullscreenQuadRenderPipeline(name, renderTarget, quad, pixelShader, setCallPixelShaderResource)
{
}

void DefferedRenderingRenderPipeline::LightingPass::setGBuffer(const cg::GBuffer& gbuffer)
{
	m_gbuffer = gbuffer;
}
