#include "ForwardRenderingRenderPipeline.hpp"





std::shared_ptr<cg::IDepthStencilBuffer> ForwardRenderingRenderPipeline::getDepthStencilBuffer() const noexcept
{
    return m_depthStencilBuffer;
}

std::shared_ptr<cg::IRenderTarget> ForwardRenderingRenderPipeline::getRenderTarget() const noexcept
{
    return m_renderTarget;
}

ForwardRenderingRenderPipeline::ForwardRenderingRenderPipeline(const std::string& name, std::shared_ptr<cg::IRenderTarget> renderTarget, std::shared_ptr<cg::IDepthStencilBuffer> depthStencilBuffer)
    : RenderPipelineWithImGuiComponents(name),
      m_renderTarget(renderTarget),
      m_depthStencilBuffer(depthStencilBuffer)
{
}
