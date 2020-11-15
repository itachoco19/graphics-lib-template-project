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
