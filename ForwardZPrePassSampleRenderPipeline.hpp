#pragma once
#include "ZPrePassForwardRendering.hpp"





class ForwardZPrePassSampleRenderPipeline
	: public ZPrePassForwardRendering
{
public:
	ForwardZPrePassSampleRenderPipeline(std::shared_ptr<cg::IRenderTarget> renderTarget);
};
