#include "GeometryRenderPipeline.hpp"





GeometryRenderPipeline::GeometryRenderPipeline(const std::string& name, std::shared_ptr<cg::IMultipleRenderTargets> mrt, std::shared_ptr<cg::IDepthStencilBuffer> depthStencilBuffer, const cg::GBuffer& gbuffer, const TargetRenderingGroupNameList& targetRenderingGroupNameList, std::shared_ptr<cg::MaterialConstantBuffer> materialConstantBuffer, std::shared_ptr<cg::TransformConstantBuffer> transformConstantBuffer, const cg::RasterizationBasedRenderPipeline::ShaderDict& shaderDict, AdditionalSetCallScene additionalSetCall)
	: GeometryRenderPipeline(name, mrt, depthStencilBuffer, gbuffer, targetRenderingGroupNameList, materialConstantBuffer, transformConstantBuffer, cg::API::shared.graphics()->createDepthStencilTester(cg::ComparisonFunction::less, cg::ComparisonFunction::always, true, false, true), shaderDict, additionalSetCall)
{
}

GeometryRenderPipeline::GeometryRenderPipeline(const std::string& name, std::shared_ptr<cg::IMultipleRenderTargets> mrt, std::shared_ptr<cg::IDepthStencilBuffer> depthStencilBuffer, const cg::GBuffer& gbuffer, const TargetRenderingGroupNameList& targetRenderingGroupNameList, std::shared_ptr<cg::MaterialConstantBuffer> materialConstantBuffer, std::shared_ptr<cg::TransformConstantBuffer> transformConstantBuffer, std::shared_ptr<cg::IDepthStencilTester> depthTesterLessFunction, const cg::RasterizationBasedRenderPipeline::ShaderDict& shaderDict, AdditionalSetCallScene additionalSetCall)
	: RenderPipelineMRTWithImGuiComponents(name, targetRenderingGroupNameList, mrt, depthStencilBuffer, materialConstantBuffer, transformConstantBuffer, nullptr, depthTesterLessFunction, shaderDict),
	  m_additionalSetCall(additionalSetCall)
{
	m_GBuffer = gbuffer;
}

void GeometryRenderPipeline::render(const cg::Scene& scene, const cg::Camera& customCamera)
{
	m_multipleRenderTarget->refreshAll();
	m_depthStencilBuffer->refresh();

	renderDefault(scene, customCamera, true, [&](const cg::Scene&) { m_multipleRenderTarget->set(m_depthStencilBuffer); m_additionalSetCall(scene); }, []() {});
}

void GeometryRenderPipeline::render(const cg::Scene& scene)
{
	render(scene, scene.camera);
}

void GeometryRenderPipeline::render()
{

}

void GeometryRenderPipeline::drawImGuiComponents()
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
		const auto imageSize = image->getSize()/5;
		ImGui::Image(image, ImVec2(imageSize.x, imageSize.y));

		ImGui::TreePop();
	}
}
