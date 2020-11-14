#pragma once
#include "GeometryRenderPipeline.hpp"
#include "RenderPipelineWithImGuiComponents.hpp"





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