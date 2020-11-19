#pragma once
#include "RenderPipelineWithImGuiComponents.hpp"





class ForwardRenderPipeline
	: public RenderPipelineWithImGuiComponents
{
private:
	std::shared_ptr<cg::IRenderTarget> m_renderTarget;
	std::shared_ptr<cg::IDepthStencilBuffer> m_depthStencilBuffer;
public:
	ForwardRenderPipeline(const std::string& name, std::shared_ptr<cg::IRenderTarget> renderTarget, std::shared_ptr<cg::IDepthStencilBuffer> depthStencilBuffer);
	virtual ~ForwardRenderPipeline() = default;

	[[nodiscard]] std::shared_ptr<cg::IRenderTarget> getRenderTarget() const noexcept;
	[[nodiscard]] std::shared_ptr<cg::IDepthStencilBuffer> getDepthStencilBuffer() const noexcept;
};
