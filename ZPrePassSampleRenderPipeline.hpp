#pragma once
#include "ZPrePassForwardRendering.hpp"





class ZPrePassSampleRenderPipeline
	: public ZPrePassForwardRendering
{
public:
	ZPrePassSampleRenderPipeline(const std::string& name, std::shared_ptr<cg::IRenderTarget> renderTarget, std::shared_ptr<cg::IDepthStencilBuffer> depthStencilBuffer);
};
