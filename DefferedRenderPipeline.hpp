#pragma once
#include "GeometryRenderPipeline.hpp"
#include "FullscreenQuadRenderPipeline.hpp"
#include "RenderPipelineWithImGuiComponents.hpp"





class DefferedRenderPipeline
	: public RenderPipelineWithImGuiComponents
{
public:
	class GeometryPass
		: public RenderPipelineWithImGuiComponents
	{
	public:
		using GeometryRenderPipelineList = std::list<std::shared_ptr<GeometryRenderPipeline>>;
	private:
		GeometryRenderPipelineList m_geometryRenderPipelineList;
	public:
		GeometryPass(const std::string& name, const GeometryRenderPipelineList& geometryRenderPipelineList);

		void render(const cg::Scene& scene, cg::Camera& customCamera);
		void render(const cg::Scene& scene) override;
		void render() override;
		
		void drawImGuiComponents() override;
	};
	class LightingPass
		: public FullscreenQuadRenderPipeline
	{
	public:
		using ShaderResourceGBufferSetCall = std::function<void(const cg::GBuffer& gbuffer, const std::shared_ptr<cg::ITextureSampler> gbufferSampler)>;
	private:
		cg::GBuffer m_GBuffer;
	public:
		LightingPass(const std::string& name, std::shared_ptr<cg::IRenderTarget> renderTarget, std::shared_ptr<cg::TransformConstantBuffer> transformConstantBuffer, std::shared_ptr<cg::LightConstantBuffer> lightConstantBuffer, std::shared_ptr<cg::IPixelShader> pixelShader, const cg::GBuffer& gbuffer, std::shared_ptr<cg::ITextureSampler> gbufferSampler, const ShaderResourceGBufferSetCall& shaderResourceSetCall, const FullscreenQuad& quad = FullscreenQuad());

		void drawImGuiComponents() override;
	};
private:
	GeometryPass m_geometryPass;
	LightingPass m_lightingPass;
protected:
	[[nodiscard]] GeometryPass accessToGeometryPass() const noexcept;
	[[nodiscard]] LightingPass accessToLightingPass() const noexcept;
public:
	DefferedRenderPipeline(const std::string& name, const GeometryPass& geometryPass, const LightingPass& lightingPass);
	virtual ~DefferedRenderPipeline() = default;
};