#pragma once
#include "DepthRenderPipeline.hpp"
#include "RenderPipelineWithImGuiComponents.hpp"




class DepthPass
	: public RenderPipelineWithImGuiComponents
{
public:
	using DepthRenderPipelineList = std::list<std::shared_ptr<DepthRenderPipeline>>;
private:
	DepthRenderPipelineList m_zRenderPipelineList;
public:
	DepthPass(const std::string& name, const DepthRenderPipelineList& zRenderPipelineList);

	void render(const cg::Scene& scene, cg::Camera& customCamera);
	void render(const cg::Scene& scene) override;
	void render() override;

	void initializeDepthStencilBuffer(std::shared_ptr<cg::IDepthStencilBuffer> depthStencilBuffer);

	void drawImGuiComponents() override;
};