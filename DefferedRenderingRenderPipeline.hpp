#pragma once
#include "FullscreenQuadRenderPipeline.hpp"
#include "RenderPipelineWithImGuiComponents.hpp"





class DefferedRenderingRenderPipeline
	: public RenderPipelineWithImGuiComponents
{
public:
	using GeometryPass = std::shared_ptr<cg::RenderPipelineMRT>;
	class LightingPass
		: public FullscreenQuadRenderPipeline
	{
	protected:
		cg::GBuffer m_gbuffer;
	public:
		LightingPass(const std::string& name, std::shared_ptr<cg::IPixelShader> pixelShader, const ShaderResourceSetCall& setCallPixelShaderResource);
		LightingPass(const std::string& name, std::shared_ptr<cg::IRenderTarget> renderTarget, std::shared_ptr<cg::IPixelShader> pixelShader, const ShaderResourceSetCall& setCallPixelShaderResource);
		LightingPass(const std::string& name, std::shared_ptr<cg::IRenderTarget> renderTarget, const FullscreenQuad& quad, std::shared_ptr<cg::IPixelShader> pixelShader, const ShaderResourceSetCall& setCallPixelShaderResource);

		void setGBuffer(const cg::GBuffer& gbuffer);
	};
private:
	GeometryPass m_geometryPass;
	LightingPass m_lightingPass;
public:
	DefferedRenderingRenderPipeline(const std::string& name, const GeometryPass& geometryPass, const LightingPass& lightingPass);
	virtual ~DefferedRenderingRenderPipeline() = default;

	void render() override;
	void render(const cg::Scene& scene) override;
};