#include "ForwardZPrePassSampleRenderPipeline.hpp"
#include "ForwardSampleRenderPipeline.hpp"





ForwardZPrePassSampleRenderPipeline::ForwardZPrePassSampleRenderPipeline(std::shared_ptr<cg::IRenderTarget> renderTarget)
	: ZPrePassForwardRendering("Z Pre-Pass Forward Rendering", DepthPass("Depth Pass", { std::make_shared<Position3Normal3DepthRenderPipeline>(cg::RasterizationBasedRenderPipeline::TargetRenderingGroupNameList{"SimpleShading"}) }), std::make_shared<ForwardSampleRenderPipeline>(renderTarget, cg::API::shared.graphics()->createDepthStencilTester(cg::ComparisonFunction::equal, cg::ComparisonFunction::always, true, false, true), false, false))
{
}
