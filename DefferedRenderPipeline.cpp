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





DefferedRenderPipeline::LightingPass::LightingPass(const std::string& name, std::shared_ptr<cg::IRenderTarget> renderTarget, std::shared_ptr<cg::TransformConstantBuffer> transformConstantBuffer, std::shared_ptr<cg::LightConstantBuffer> lightConstantBuffer, std::shared_ptr<cg::IPixelShader> pixelShader, const cg::GBuffer& gbuffer, std::shared_ptr<cg::ITextureSampler> gbufferSampler, const ShaderResourceGBufferSetCall& shaderResourceSetCall, const FullscreenQuad& quad)
	: FullscreenQuadRenderPipeline(name, renderTarget, transformConstantBuffer, lightConstantBuffer, pixelShader, [=]() { shaderResourceSetCall(gbuffer, gbufferSampler); }, quad),
	  m_GBuffer(gbuffer)
{
}

void DefferedRenderPipeline::LightingPass::drawImGuiComponents()
{
	if (ImGui::TreeNode("GBuffer"))
	{
		static std::string bufferName = "";
		const auto contents = m_GBuffer.getAllContents();

		for (const auto content : contents)
		{
			if (ImGui::Button(content.name.c_str()))
			{
				bufferName = content.name;
			}
		}
		if (bufferName == "") { return; }

		const auto image = m_GBuffer.get(bufferName);
		const auto imageSize = image->getSize() / 5;
		ImGui::Image(image, ImVec2(imageSize.x, imageSize.y));

		ImGui::TreePop();
	}
}
