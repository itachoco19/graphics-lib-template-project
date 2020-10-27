#include "FullscreenQuadRenderPipeline.hpp"





FullscreenQuadRenderPipeline::FullscreenQuadRenderPipeline(const std::string& name, std::shared_ptr<cg::IPixelShader> pixelShader, const ShaderResourceSetCall& setCallPixelShaderResource)
	: FullscreenQuadRenderPipeline(name, cg::MainRenderTarget::shared.get(), pixelShader, setCallPixelShaderResource)
{
}
FullscreenQuadRenderPipeline::FullscreenQuadRenderPipeline(const std::string& name, std::shared_ptr<cg::IRenderTarget> renderTarget, std::shared_ptr<cg::IPixelShader> pixelShader, const ShaderResourceSetCall& setCallPixelShaderResource)
	: FullscreenQuadRenderPipeline(name, renderTarget, FullscreenQuad(), pixelShader, setCallPixelShaderResource)
{
}
FullscreenQuadRenderPipeline::FullscreenQuadRenderPipeline(const std::string& name, std::shared_ptr<cg::IRenderTarget> renderTarget, const FullscreenQuad& quad, std::shared_ptr<cg::IPixelShader> pixelShader, const ShaderResourceSetCall& setCallPixelShaderResource)
	: RenderPipelineSRT(name, { "" }, renderTarget, nullptr, nullptr, nullptr, nullptr, nullptr,
	  {
		  { cg::ShaderStage::vs, std::dynamic_pointer_cast<cg::IVertexShader>(cg::ShaderPool::shared.createFromFileAndAdd(cg::ShaderStage::vs, "FullscreenQuad.vsh", "FullscreenQuad.vsh", "vs_main", "vs_5_0")) },
		  { cg::ShaderStage::ps, pixelShader }
	  }),
	  m_additionalSetCall(setCallPixelShaderResource),
	  m_quad(quad)
{
	m_rasterizer = cg::API::shared.graphics()->createRasterizer();
}

void FullscreenQuadRenderPipeline::render()
{
	auto setCall = [&]()
	{
		m_renderTarget->refresh();
		m_renderTarget->set(nullptr);

		m_additionalSetCall();
	};
	auto drawCall = [&]()
	{
		m_quad->parts.at("main").getGeometryBuffer()->draw(m_quad->primitiveTopology, m_quad->instanceCount);
	};

	renderDefault(setCall, drawCall);
}

void FullscreenQuadRenderPipeline::render(const cg::Scene& scene)
{
}
