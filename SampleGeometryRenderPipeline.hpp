#pragma once
#include "GeometryRenderPipeline.hpp"





class SampleGeometryRenderPipeline
	: public GeometryRenderPipeline
{
private:
	AdditionalSetCallScene m_additionalSetCall;
public:
	SampleGeometryRenderPipeline(std::shared_ptr<cg::IMultipleRenderTarget> mrt, std::shared_ptr<cg::IDepthStencilBuffer> depthStencilBuffer, std::shared_ptr<cg::IDepthStencilBuffer> shadowMap, const TargetRenderingGroupNameList& targetRenderingGroupNameList);
	virtual ~SampleGeometryRenderPipeline() = default;

	void drawImGuiComponents() override;
};