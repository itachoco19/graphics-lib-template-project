#pragma once
#include "GeometryRenderPipeline.hpp"
#include "FullscreenQuadRenderPipeline.hpp"
#include "RenderPipelineWithImGuiComponents.hpp"





class DefferedRenderingRenderPipeline
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

		cg::GBuffer getGBuffer() const;
		void initializeMultipleRenderTarget(std::shared_ptr<cg::IMultipleRenderTarget> multipleRenderTarget);
		void initializeDepthStencilBuffer(std::shared_ptr<cg::IDepthStencilBuffer> depthStencilBuffer);

		void drawImGuiComponents() override;
	};
	class LightingPass
		: public FullscreenQuadRenderPipeline
	{
	public:
		using ShaderResourceGBufferSetCall = std::function<void(const cg::GBuffer&)>;
	public:
		LightingPass(const std::string& name, std::shared_ptr<cg::LightConstantBuffer> lightConstantBuffer, std::shared_ptr<cg::IPixelShader> pixelShader, const cg::GBuffer& gbuffer, const ShaderResourceGBufferSetCall& shaderResourceSetCall);
		LightingPass(const std::string& name, std::shared_ptr<cg::IRenderTarget> renderTarget, std::shared_ptr<cg::LightConstantBuffer> lightConstantBuffer, std::shared_ptr<cg::IPixelShader> pixelShader, const cg::GBuffer& gbuffer, const ShaderResourceGBufferSetCall& shaderResourceSetCall);
		LightingPass(const std::string& name, std::shared_ptr<cg::IRenderTarget> renderTarget, std::shared_ptr<cg::LightConstantBuffer> lightConstantBuffer, const FullscreenQuad& quad, std::shared_ptr<cg::IPixelShader> pixelShader, const cg::GBuffer& gbuffer, const ShaderResourceGBufferSetCall& shaderResourceSetCall);
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