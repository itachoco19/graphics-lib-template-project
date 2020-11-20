#pragma once
#include "ForwardZPrePassRenderPipeline.hpp"





class ForwardZPrePassSampleRenderPipeline
	: public ForwardZPrePassRenderPipeline
{
public:
	static const std::string targetRenderingGroupName;
public:
	ForwardZPrePassSampleRenderPipeline(std::shared_ptr<cg::IRenderTarget> renderTarget);
};
