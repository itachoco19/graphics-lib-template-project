#pragma once
#include "RenderPipelineWithImGuiComponents.hpp"





class ForwardRenderingRenderPipeline
	: public RenderPipelineWithImGuiComponents
{
private:
	std::shared_ptr<cg::IRenderTarget> m_renderTarget;
	std::shared_ptr<cg::IDepthStencilBuffer> m_depthStencilBuffer;
public:
	ForwardRenderingRenderPipeline(const std::string& name, std::shared_ptr<cg::IRenderTarget> renderTarget, std::shared_ptr<cg::IDepthStencilBuffer> depthStencilBuffer);
	virtual ~ForwardRenderingRenderPipeline() = default;

	[[nodiscard]] std::shared_ptr<cg::IRenderTarget> getRenderTarget() const noexcept;
	[[nodiscard]] std::shared_ptr<cg::IDepthStencilBuffer> getDepthStencilBuffer() const noexcept;
};
