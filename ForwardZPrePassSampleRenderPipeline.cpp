#include "ForwardZPrePassSampleRenderPipeline.hpp"
#include "ForwardSampleRenderPipeline.hpp"





const std::string ForwardZPrePassSampleRenderPipeline::targetRenderingGroupName = "Sample";

ForwardZPrePassSampleRenderPipeline::ForwardZPrePassSampleRenderPipeline(std::shared_ptr<cg::IRenderTarget> renderTarget)
	: ForwardZPrePassRenderPipeline("Forward Z Pre-Pass Sample Render Pipeline", DepthPass("Depth Pass", { std::make_shared<Position3Normal3DepthRenderPipeline>(cg::RasterizationBasedRenderPipeline::TargetRenderingGroupNameList{"Sample"}) }), std::make_shared<ForwardSampleRenderPipeline>(renderTarget, cg::API::shared.graphics()->createDepthStencilTester(cg::ComparisonFunction::equal, cg::ComparisonFunction::always, true, false, true), false, false))
{
}
