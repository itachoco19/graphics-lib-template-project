#pragma once
#include "DepthRenderPipeline.hpp"
#include "RenderPipelineWithImGuiComponents.hpp"




class DepthPass
	: public RenderPipelineWithImGuiComponents
{
public:
	using DepthRenderPipelineList = std::list<std::shared_ptr<DepthRenderPipeline>>;
private:
	std::shared_ptr<cg::IDepthStencilBuffer> m_depthStencilBuffer;
	DepthRenderPipelineList m_zRenderPipelineList;
public:
	DepthPass(const std::string& name, const DepthRenderPipelineList& zRenderPipelineList, std::shared_ptr<cg::IDepthStencilBuffer> depthStencilBuffer);

	void render(const cg::Scene& scene, cg::Camera& customCamera);
	void render(const cg::Scene& scene) override;
	void render() override;

	void drawImGuiComponents() override;
};