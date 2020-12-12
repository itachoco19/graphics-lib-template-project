#pragma once
#include "RenderPipelineSRTWithImGuiComponents.hpp"
#include "FullScreenQuad.hpp"
#include <GraphicsLib.hpp>





class FullscreenQuadRenderPipeline
	: public RenderPipelineSRTWithImGuiComponents
{
public:
	using ShaderResourceSetCall = std::function<void()>;
private:
	ShaderResourceSetCall m_additionalSetCall;

	FullscreenQuad m_quad;
public:
	FullscreenQuadRenderPipeline(const std::string& name, std::shared_ptr<cg::IRenderTarget> renderTarget, std::shared_ptr<cg::TransformConstantBuffer> transformConstantBuffer, std::shared_ptr<cg::LightConstantBuffer> lightConstantBuffer, std::shared_ptr<cg::IPixelShader> pixelShader, const ShaderResourceSetCall& setCallPixelShaderResource, const FullscreenQuad& quad = FullscreenQuad());



	void render() override;
	void render(const cg::Scene& scene) override;

	virtual void drawImGuiComponents() override;
};
