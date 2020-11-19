#include "ForwardZPrePassSampleRenderPipeline.hpp"
#include "ForwardSampleRenderPipeline.hpp"





ForwardZPrePassSampleRenderPipeline::ForwardZPrePassSampleRenderPipeline(const std::string& name, std::shared_ptr<cg::IRenderTarget> renderTarget, std::shared_ptr<cg::IDepthStencilBuffer> depthStencilBuffer)
	: ZPrePassForwardRendering(name, DepthPass(name, { std::make_shared<Position3Normal3DepthRenderPipeline>(cg::RasterizationBasedRenderPipeline::TargetRenderingGroupNameList{"SimpleShading"}) }), std::make_shared<ForwardSampleRenderPipeline>(renderTarget, depthStencilBuffer, cg::API::shared.graphics()->createDepthStencilTester(cg::ComparisonFunction::equal, cg::ComparisonFunction::always, true, false, true), false, false))
{
}
