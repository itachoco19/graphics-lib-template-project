#include "FullscreenQuadRenderPipeline.hpp"





FullscreenQuadRenderPipeline::FullscreenQuadRenderPipeline(const std::string& name, std::shared_ptr<cg::IRenderTarget> renderTarget, std::shared_ptr<cg::TransformConstantBuffer> transformConstantBuffer, std::shared_ptr<cg::LightConstantBuffer> lightConstantBuffer, std::shared_ptr<cg::IPixelShader> pixelShader, const ShaderResourceSetCall& setCallPixelShaderResource, const FullscreenQuad& quad)
	: RenderPipelineSRTWithImGuiComponents(name, { "" }, renderTarget, nullptr, nullptr, transformConstantBuffer, lightConstantBuffer, nullptr,
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
		m_renderTarget->set(nullptr);

		m_additionalSetCall();
	};
	auto drawCall = [&]()
	{
		m_quad->parts.at("main").getGeometryBuffer()->draw(m_quad->primitiveTopology, m_quad->instanceCount);
	};

	m_renderTarget->refresh();
	renderDefault(setCall, drawCall);
}

void FullscreenQuadRenderPipeline::render(const cg::Scene& scene)
{
	auto setCall = [&](const cg::Scene& scene_)
	{
		m_renderTarget->set(nullptr);

		m_additionalSetCall();
	};
	auto drawCall = [&]()
	{
		m_quad->parts.at("main").getGeometryBuffer()->draw(m_quad->primitiveTopology, m_quad->instanceCount);
	};

	m_renderTarget->refresh();
	renderDefault(scene, false, setCall, drawCall);
}

void FullscreenQuadRenderPipeline::drawImGuiComponents()
{
}
