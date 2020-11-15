#pragma once
#include "FullScreenQuad.hpp"
#include <GraphicsLib.hpp>





class FullscreenQuadRenderPipeline
	: public cg::RenderPipelineSRT
{
public:
	using ShaderResourceSetCall = std::function<void()>;
private:
	ShaderResourceSetCall m_additionalSetCall;

	FullscreenQuad m_quad;
public:
	FullscreenQuadRenderPipeline(const std::string& name, std::shared_ptr<cg::LightConstantBuffer> lightConstantBuffer, std::shared_ptr<cg::IPixelShader> pixelShader, const ShaderResourceSetCall& setCallPixelShaderResource);
	FullscreenQuadRenderPipeline(const std::string& name,  std::shared_ptr<cg::IRenderTarget> renderTarget, std::shared_ptr<cg::LightConstantBuffer> lightConstantBuffer, std::shared_ptr<cg::IPixelShader> pixelShader, const ShaderResourceSetCall& setCallPixelShaderResource);
	FullscreenQuadRenderPipeline(const std::string& name, std::shared_ptr<cg::IRenderTarget> renderTarget, const FullscreenQuad& quad, std::shared_ptr<cg::LightConstantBuffer> lightConstantBuffer, std::shared_ptr<cg::IPixelShader> pixelShader, const ShaderResourceSetCall& setCallPixelShaderResource);



	void render() override;
	void render(const cg::Scene& scene) override;
};
