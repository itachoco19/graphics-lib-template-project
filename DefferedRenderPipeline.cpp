#include "DefferedRenderPipeline.hpp"





DefferedRenderPipeline::GeometryPass DefferedRenderPipeline::accessToGeometryPass() const noexcept
{
	return m_geometryPass;
}

DefferedRenderPipeline::LightingPass DefferedRenderPipeline::accessToLightingPass() const noexcept
{
	return m_lightingPass;
}

DefferedRenderPipeline::DefferedRenderPipeline(const std::string& name, const GeometryPass& geometryPass, const LightingPass& lightingPass)
	: RenderPipelineWithImGuiComponents(name),
	  m_geometryPass(geometryPass),
	  m_lightingPass(lightingPass)
{
}





DefferedRenderPipeline::GeometryPass::GeometryPass(const std::string& name, const GeometryRenderPipelineList& geometryRenderPipelineList)
	: RenderPipelineWithImGuiComponents(name),
	m_geometryRenderPipelineList(geometryRenderPipelineList)
{
}

void DefferedRenderPipeline::GeometryPass::render(const cg::Scene& scene, cg::Camera& customCamera)
{
	for (auto geometryRenderPipeline : m_geometryRenderPipelineList)
	{
		geometryRenderPipeline->render(scene, customCamera);
	}
}

void DefferedRenderPipeline::GeometryPass::render(const cg::Scene& scene)
{
	for (auto geometryRenderPipeline : m_geometryRenderPipelineList)
	{
		geometryRenderPipeline->render(scene);
	}
}

void DefferedRenderPipeline::GeometryPass::render()
{

	for (auto geometryRenderPipeline : m_geometryRenderPipelineList)
	{
		geometryRenderPipeline->render();
	}
}

cg::GBuffer DefferedRenderPipeline::GeometryPass::getGBuffer() const
{
	if (m_geometryRenderPipelineList.empty())
	{
		return cg::GBuffer();
	}
	return m_geometryRenderPipelineList.begin()->get()->getGBuffer();
}

void DefferedRenderPipeline::GeometryPass::initializeMultipleRenderTarget(std::shared_ptr<cg::IMultipleRenderTarget> multipleRenderTarget)
{
	for (auto geometryRenderPipeline : m_geometryRenderPipelineList)
	{
		geometryRenderPipeline->initializeMultipleRenderTarget(multipleRenderTarget);
	}
}

void DefferedRenderPipeline::GeometryPass::initializeDepthStencilBuffer(std::shared_ptr<cg::IDepthStencilBuffer> depthStencilBuffer)
{
	for (auto geometryRenderPipeline : m_geometryRenderPipelineList)
	{
		geometryRenderPipeline->initializeDepthStencilBuffer(depthStencilBuffer);
	}
}

void DefferedRenderPipeline::GeometryPass::drawImGuiComponents()
{
	for (auto geometryRenderPipeline : m_geometryRenderPipelineList)
	{
		if (ImGui::TreeNode(geometryRenderPipeline->name().c_str()))
		{
			geometryRenderPipeline->drawImGuiComponents();

			ImGui::TreePop();
		}
	}
}





const auto createShaderResourceSetCall = [](const DefferedRenderPipeline::LightingPass::ShaderResourceGBufferSetCall& shaderResourceGBufferSetCall, const DefferedRenderPipeline::GeometryPass& geometryPass)
{
	return [=](){ shaderResourceGBufferSetCall(geometryPass.getGBuffer()); };
};

DefferedRenderPipeline::LightingPass::LightingPass(const std::string& name, std::shared_ptr<cg::TransformConstantBuffer> transformConstantBuffer, std::shared_ptr<cg::LightConstantBuffer> lightConstantBuffer, std::shared_ptr<cg::IPixelShader> pixelShader, const GeometryPass& geometryPass, const ShaderResourceGBufferSetCall& shaderResourceSetCall)
	: FullscreenQuadRenderPipeline(name, transformConstantBuffer, lightConstantBuffer, pixelShader, createShaderResourceSetCall(shaderResourceSetCall, geometryPass))
{
}

DefferedRenderPipeline::LightingPass::LightingPass(const std::string& name, std::shared_ptr<cg::IRenderTarget> renderTarget, std::shared_ptr<cg::TransformConstantBuffer> transformConstantBuffer, std::shared_ptr<cg::LightConstantBuffer> lightConstantBuffer, std::shared_ptr<cg::IPixelShader> pixelShader, const GeometryPass& geometryPass, const ShaderResourceGBufferSetCall& shaderResourceSetCall)
	: FullscreenQuadRenderPipeline(name, renderTarget, transformConstantBuffer, lightConstantBuffer, pixelShader, createShaderResourceSetCall(shaderResourceSetCall, geometryPass))
{
}

DefferedRenderPipeline::LightingPass::LightingPass(const std::string& name, std::shared_ptr<cg::IRenderTarget> renderTarget, std::shared_ptr<cg::TransformConstantBuffer> transformConstantBuffer, std::shared_ptr<cg::LightConstantBuffer> lightConstantBuffer, const FullscreenQuad& quad, std::shared_ptr<cg::IPixelShader> pixelShader, const GeometryPass& geometryPass, const ShaderResourceGBufferSetCall& shaderResourceSetCall)
	: FullscreenQuadRenderPipeline(name, renderTarget, quad, transformConstantBuffer, lightConstantBuffer, pixelShader, createShaderResourceSetCall(shaderResourceSetCall, geometryPass))
{
}
