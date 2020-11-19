#pragma once
#include "ZPrePassForwardRendering.hpp"





class ForwardZPrePassSampleRenderPipeline
	: public ZPrePassForwardRendering
{
public:
	ForwardZPrePassSampleRenderPipeline(const std::string& name, std::shared_ptr<cg::IRenderTarget> renderTarget, std::shared_ptr<cg::IDepthStencilBuffer> depthStencilBuffer);
};
