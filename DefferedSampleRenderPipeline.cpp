#include "DefferedSampleRenderPipeline.hpp"
#include "SimpleDirectionalLight.hpp"
#include "SimplePointLight.hpp"
#include "SampleGeometryRenderPipeline.hpp"
#include "SampleGBuffer.hpp"




const std::string DefferedSampleRenderPipeline::targetRenderingGroupName = "Sample";
const cg::RasterizationBasedRenderPipeline::TargetRenderingGroupNameList targetRenderingGroupNameList = { DefferedSampleRenderPipeline::targetRenderingGroupName };





const auto createMRT = [](const cpp::Vector2D<int>& lightingPassRenderTargetSize)
{
	return 
	cg::API::shared.graphics()->createMultipleRenderTarget
	(
		lightingPassRenderTargetSize,
		{
			cg::API::shared.graphics()->createRenderTarget // Base Color + Roughness
			(
				lightingPassRenderTargetSize,
				cg::TextureFormat::R32G32B32A32_FLOAT
			),
			cg::API::shared.graphics()->createRenderTarget // Normal + Metalness
			(
				lightingPassRenderTargetSize,
				cg::TextureFormat::R32G32B32A32_FLOAT
			),
			cg::API::shared.graphics()->createRenderTarget // IOR
			(
				lightingPassRenderTargetSize,
				cg::TextureFormat::R32_FLOAT
			),
		}
	);
};
const auto constructGeometryPass = [](const cg::RasterizationBasedRenderPipeline::TargetRenderingGroupNameList& targetRenderingGroupNameList, std::shared_ptr<cg::IRenderTarget> lightingPassRenderTarget, std::shared_ptr<cg::IMultipleRenderTarget> geometryPassMRT, std::shared_ptr<cg::IDepthStencilBuffer> geometryPassDepthStencilBuffer, std::shared_ptr<cg::IDepthStencilBuffer> shadowMap)
{
	auto geometryPass = 
	DefferedRenderPipeline::GeometryPass
	(
		"Sample Geometry Pass",
		{
			std::make_shared<SampleGeometryRenderPipeline>
			(
				geometryPassMRT,
				geometryPassDepthStencilBuffer,
				shadowMap,				
				targetRenderingGroupNameList
			)
		}
	);

	geometryPass.initializeMultipleRenderTarget(geometryPassMRT);
	geometryPass.initializeDepthStencilBuffer(geometryPassDepthStencilBuffer);

	return geometryPass;
};









DefferedSampleRenderPipeline::DefferedSampleRenderPipeline(std::shared_ptr<cg::IRenderTarget> lightingPassRenderTarget, const GeometryPass& geometryPass, std::shared_ptr<cg::ITextureSampler> gbufferSampler, std::shared_ptr<cg::IDepthStencilBuffer> shadowMap)
	: DefferedRenderPipeline
	  (
		  "Deffered Sample Render Pipeline",
		  geometryPass,
		  DefferedRenderPipeline::LightingPass
		  (
			  "Sample Lighting Pass",
			  lightingPassRenderTarget,
			  std::make_shared<cg::TransformConstantBuffer>
			  (
				  cg::TransformConstantBuffer::BufferDict
				  {
					  {
						  cg::ShaderStage::ps,

						  std::make_shared<cg::TransformConstantBuffer::ElementBuffer>
						  (
							  cg::TransformConstantBuffer::ElementBuffer::constructor<constant::Transform_InvV_InvP_LVP>
							  (
								  [](constant::Transform_InvV_InvP_LVP& data, const cg::Scene& s, const cg::Transform& t, const cg::Camera& c)
								  {
									  cg::TransformConstantBufferHelper::storeInvV(&data.invV, c);
									  cg::TransformConstantBufferHelper::storeInvP(&data.invP, c);
									
									  const auto keyLight = std::dynamic_pointer_cast<SimpleDirectionalLight>(s.getLightDict().at("Key"));
									  cg::TransformConstantBufferHelper::storeVP(&data.lvp, keyLight->perspective);
								  }
							  )
						  )
					  }
				  }
			  ),
			  std::make_shared<cg::LightConstantBuffer>
			  (
				  cg::LightConstantBuffer::BufferDict
				  {
					  {
						  cg::ShaderStage::ps,

						  std::make_shared<cg::LightConstantBuffer::ElementBuffer>
						  (
							  cg::LightConstantBuffer::ElementBuffer::constructor<constant::SimpleLight>
							  (
								  [&](constant::SimpleLight& data, const cg::Scene& scene)
								  {
									  auto pointLights = scene.getLights(SimplePointLight::type);
									  auto pointLightSrc = std::dynamic_pointer_cast<SimplePointLight>(scene.getLights(SimplePointLight::type).at("Back"));
									  auto& pointLightDest = data.pointLights[0];
									  pointLightDest = pointLightSrc->getConstant().get<constant::SimplePointLight>();
									  cpp::assignVector3DToArray4(&pointLightDest.position, pointLightSrc->getTransformRef().calcPositionWorld());

									  auto directionalLightSrc = std::dynamic_pointer_cast<SimpleDirectionalLight>(scene.getLights(SimpleDirectionalLight::type).at("Key"));
									  auto& directionalLightDest = data.directionalLight;
									  directionalLightDest = directionalLightSrc->getConstant().get<constant::SimpleDirectionalLight>();
									  cpp::assignVector3DToArray4(&directionalLightDest.direction, directionalLightSrc->perspective.getTransformRef().calcForwardWorld());

									  cpp::assignVector3DToArray4(&data.cameraPosition, scene.camera.getTransformRef().calcPositionLocal());
								  }
							  )
						  )
					  }
				  }
		      ),
			  std::dynamic_pointer_cast<cg::IPixelShader>(cg::ShaderPool::shared.createFromFileAndAdd(cg::ShaderStage::ps, "SampleLightingPass.psh", "SampleLightingPass.psh", "ps_main", "ps_4_0")),
			  geometryPass.getGBuffer(),
			  [=](const cg::GBuffer& gbuffer)
			  {
				  auto locationDict = cg::ShaderPool::shared.get(cg::ShaderStage::ps, "SampleLightingPass.psh")->getResourceLocationDict();
			      
				  auto gbufferLocationDict = locationDict.at(cg::ShaderResourceType::Texture);
				  gbuffer.get(SampleGBuffer::BaseColorRoughness)->set(cg::ShaderStage::ps, gbufferLocationDict.at("baseColorRoughnessMap"), cg::GPUAccessFlags::R);
				  gbuffer.get(SampleGBuffer::NormalMetalness)   ->set(cg::ShaderStage::ps, gbufferLocationDict.at("normalMetalnessMap"),    cg::GPUAccessFlags::R);
				  gbuffer.get(SampleGBuffer::IOR)               ->set(cg::ShaderStage::ps, gbufferLocationDict.at("iorMap"),                cg::GPUAccessFlags::R);
				  gbuffer.get(SampleGBuffer::Depth)             ->set(cg::ShaderStage::ps, gbufferLocationDict.at("depthMap"),              cg::GPUAccessFlags::R);
				  gbuffer.get(SampleGBuffer::ShadowMap)         ->set(cg::ShaderStage::ps, gbufferLocationDict.at("shadowMap"),             cg::GPUAccessFlags::R);

				  gbufferSampler->set(cg::ShaderStage::ps, locationDict.at(cg::ShaderResourceType::TextureSampler).at("gbufferSampler"));
			  }
		  )
	  ),
	  m_shadowMapRenderingPass
	  (
		  "Shadow Map Rendering Pass", 
		  {
			  std::make_shared<Position3Normal3DepthRenderPipeline>(targetRenderingGroupNameList)
		  }
	  ),
	  m_shadowMap(shadowMap)
{
	m_shadowMapRenderingPass.initializeDepthStencilBuffer(shadowMap);
}
DefferedSampleRenderPipeline::DefferedSampleRenderPipeline(std::shared_ptr<cg::IRenderTarget> lightingPassRenderTarget, std::shared_ptr<cg::IMultipleRenderTarget> geometryPassMRT, std::shared_ptr<cg::IDepthStencilBuffer> geometryPassDepthStencilBuffer, std::shared_ptr<cg::ITextureSampler> gbufferSampler, std::shared_ptr<cg::IDepthStencilBuffer> shadowMap)
	: DefferedSampleRenderPipeline(lightingPassRenderTarget, constructGeometryPass(targetRenderingGroupNameList, lightingPassRenderTarget, geometryPassMRT, geometryPassDepthStencilBuffer, shadowMap), gbufferSampler, shadowMap)
{
}

DefferedSampleRenderPipeline::DefferedSampleRenderPipeline(std::shared_ptr<cg::IRenderTarget> lightingPassRenderTarget)
	: DefferedSampleRenderPipeline(lightingPassRenderTarget, cg::API::shared.graphics()->createTextureSampler())
{
}

DefferedSampleRenderPipeline::DefferedSampleRenderPipeline(std::shared_ptr<cg::IRenderTarget> lightingPassRenderTarget, std::shared_ptr<cg::ITextureSampler> gbufferSampler)
	: DefferedSampleRenderPipeline(lightingPassRenderTarget, createMRT(lightingPassRenderTarget->getSize()), cg::API::shared.graphics()->createDepthStencilBuffer(lightingPassRenderTarget->getSize(), cg::TextureFormat::D32_FLOAT), gbufferSampler, cg::API::shared.graphics()->createDepthStencilBuffer(lightingPassRenderTarget->getSize(), cg::TextureFormat::D32_FLOAT))
{
}

void DefferedSampleRenderPipeline::render(const cg::Scene& scene)
{
	const auto keyLight = scene.getLight<SimpleDirectionalLight>("Key");
	m_shadowMap->refresh();
	m_shadowMapRenderingPass.render(scene, keyLight->perspective);

	accessToGeometryPass().render(scene);
	accessToLightingPass().render(scene);
}

void DefferedSampleRenderPipeline::render()
{
}

void DefferedSampleRenderPipeline::drawImGuiComponents()
{
	if (ImGui::TreeNode(name().c_str()))
	{
		if (ImGui::TreeNode("Geometry Pass"))
		{
			accessToGeometryPass().drawImGuiComponents();

			ImGui::TreePop();
		}

		ImGui::TreePop();
	}
}
