#include "SampleGeometryRenderPipeline.hpp"
#include "SampleGBuffer.hpp"





SampleGeometryRenderPipeline::SampleGeometryRenderPipeline(std::shared_ptr<cg::IMultipleRenderTarget> mrt, std::shared_ptr<cg::IDepthStencilBuffer> depthStencilBuffer, std::shared_ptr<cg::IDepthStencilBuffer> shadowMap, const TargetRenderingGroupNameList& targetRenderingGroupNameList)
	: GeometryRenderPipeline
	  (
	      "Sample Geometry Render Pipeline",
		  SampleGBuffer(mrt->getRenderingResult(0), mrt->getRenderingResult(1), mrt->getRenderingResult(2), depthStencilBuffer->getDepthBufferTexture(), shadowMap->getDepthBufferTexture()),
		  targetRenderingGroupNameList,
		  std::make_shared<cg::MaterialConstantBuffer>
		  (
			  cg::MaterialConstantBuffer::BufferDict
			  {
				  {
					  cg::ShaderStage::ps,
					  std::make_shared<cg::MaterialConstantBuffer::ElementBuffer>
					  (
					      cg::MaterialConstantBuffer::ElementBuffer(sizeof(constant::SimplePBRMaterial))
					  )
				  }
			  }
		  ),
		  std::make_shared<cg::TransformConstantBuffer>
		  (
		      cg::TransformConstantBuffer::BufferDict
			  {
			      {
				      cg::ShaderStage::vs,
					  std::make_shared<cg::TransformConstantBuffer::ElementBuffer>
					  (
					      cg::TransformConstantBuffer::ElementBuffer::constructor<constant::TransformWVP_N>
						  (
						      [](constant::TransformWVP_N& data, const cg::Scene& s, const cg::Transform& t, const cg::Camera& c)
							  {
							      cg::TransformConstantBufferHelper::storeWVP(&data.wvp, t, c);
								  cg::TransformConstantBufferHelper::storeN(&data.n, t);
							  }
						  )
					  )
				  }
			  }
		  ),
		  cg::RasterizationBasedRenderPipeline::ShaderDict
		  {
		      {
			      cg::ShaderStage::vs,
				  cg::ShaderPool::shared.createFromFileAndAdd(cg::ShaderStage::vs, "SampleGeometryPass.vsh", "SampleGeometryPass.vsh", "vs_main", "vs_4_0")
			  },
			  {
				  cg::ShaderStage::ps,
				  cg::ShaderPool::shared.createFromFileAndAdd(cg::ShaderStage::ps, "SampleGeometryPass.psh", "SampleGeometryPass.psh", "ps_main", "ps_4_0")
			  }
		  }
	  )
{
}





void SampleGeometryRenderPipeline::drawImGuiComponents()
{
	if (ImGui::TreeNode("GBuffer"))
	{
		static std::string bufferName;
		if (ImGui::Button("BaseColor+Roughness"))
		{
			bufferName = "BaseColor+Roughness";
		}
		if (ImGui::Button("Normal+Metalness"))
		{
			bufferName = "Normal+Metalness";
		}
		if (ImGui::Button("IOR"))
		{
			bufferName = "IOR";
		}
		if (ImGui::Button("Depth"))
		{
			bufferName = "Depth";
		}
		if (ImGui::Button("Shadow Map"))
		{
			bufferName = "ShadowMap";
		}

		if (bufferName == "") { return; }

		const auto image = m_GBuffer.get(bufferName);
		const auto imageSize = image->getSize() / 5;
		ImGui::Image(image, ImVec2(imageSize.x, imageSize.y));

		ImGui::TreePop();
	}
}
