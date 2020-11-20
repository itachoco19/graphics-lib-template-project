#pragma once
#include "ForwardZPrePassRenderPipeline.hpp"





class ForwardZPrePassSampleRenderPipeline
	: public ForwardZPrePassRenderPipeline
{
public:
	ForwardZPrePassSampleRenderPipeline(std::shared_ptr<cg::IRenderTarget> renderTarget);
};
