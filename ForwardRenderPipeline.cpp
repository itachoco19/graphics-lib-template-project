#include "ForwardRenderPipeline.hpp"





std::shared_ptr<cg::IDepthStencilBuffer> ForwardRenderPipeline::getDepthStencilBuffer() const noexcept
{
    return m_depthStencilBuffer;
}

std::shared_ptr<cg::IRenderTarget> ForwardRenderPipeline::getRenderTarget() const noexcept
{
    return m_renderTarget;
}

ForwardRenderPipeline::ForwardRenderPipeline(const std::string& name, std::shared_ptr<cg::IRenderTarget> renderTarget, std::shared_ptr<cg::IDepthStencilBuffer> depthStencilBuffer)
    : RenderPipelineWithImGuiComponents(name),
      m_renderTarget(renderTarget),
      m_depthStencilBuffer(depthStencilBuffer)
{
}
