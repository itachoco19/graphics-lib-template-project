#include "DefferedSampleRenderPipeline.hpp"
#include "SimpleDirectionalLight.hpp"
#include "SimplePointLight.hpp"
#include "SampleGeometryRenderPipeline.hpp"
#include "SampleGBuffer.hpp"




const std::string DefferedSampleRenderPipeline::targetRenderingGroupName = "Sample";
const cg::RasterizationBasedRenderPipeline::TargetRenderingGroupNameList targetRenderingGroupNameList = { DefferedSampleRenderPipeline::targetRenderingGroupName };





const auto constructGeometryPass = [](const cg::RasterizationBasedRenderPipeline::TargetRenderingGroupNameList& targetRenderingGroupNameList, std::shared_ptr<cg::IRenderTarget> lightingPassRenderTarget, std::shared_ptr<cg::IDepthStencilBuffer> geometryPassDepthStencilBuffer, std::shared_ptr<cg::IDepthStencilBuffer> shadowMap)
{
	const auto lightingPassRenderTargetSize = lightingPassRenderTarget->getSize();
	const auto sampleCount  = lightingPassRenderTarget->getMSAASampleCount();
	const auto geometryPassMRT = 
	cg::API::shared.graphics()->createMultipleRenderTargets
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
			  geometryPass,
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
			  gbufferSampler,
			  [=](const cg::GBuffer& gbuffer_, std::shared_ptr<cg::ITextureSampler> gbufferSampler_)
			  {
				  auto locationDict = cg::ShaderPool::shared.get(cg::ShaderStage::ps, "SampleLightingPass.psh")->getResourceLocationDict();
			      
				  auto gbufferLocationDict = locationDict.at(cg::ShaderResourceType::Texture);
				  gbuffer_.get(SampleGBuffer::BaseColorRoughness)->set(cg::ShaderStage::ps, gbufferLocationDict.at("baseColorRoughnessMap"), cg::GPUAccessType::R);
				  gbuffer_.get(SampleGBuffer::NormalMetalness)   ->set(cg::ShaderStage::ps, gbufferLocationDict.at("normalMetalnessMap"),    cg::GPUAccessType::R);
				  gbuffer_.get(SampleGBuffer::IOR)               ->set(cg::ShaderStage::ps, gbufferLocationDict.at("iorMap"),                cg::GPUAccessType::R);
				  gbuffer_.get(SampleGBuffer::Depth)             ->set(cg::ShaderStage::ps, gbufferLocationDict.at("depthMap"),              cg::GPUAccessType::R);
				  gbuffer_.get(SampleGBuffer::ShadowMap)         ->set(cg::ShaderStage::ps, gbufferLocationDict.at("shadowMap"),             cg::GPUAccessType::R);

				  gbufferSampler_->set(cg::ShaderStage::ps, locationDict.at(cg::ShaderResourceType::TextureSampler).at("gbufferSampler"));
			  }
		  )
	  ),
	  m_shadowMapRenderingPass
	  (
		  "Shadow Map Rendering Pass", 
		  {
			  std::make_shared<Position3Normal3DepthRenderPipeline>(targetRenderingGroupNameList)
		  },
		  shadowMap
	  ),
	  m_shadowMap(shadowMap)
{
}
DefferedSampleRenderPipeline::DefferedSampleRenderPipeline(std::shared_ptr<cg::IRenderTarget> lightingPassRenderTarget, std::shared_ptr<cg::IDepthStencilBuffer> geometryPassDepthStencilBuffer, std::shared_ptr<cg::ITextureSampler> gbufferSampler, std::shared_ptr<cg::IDepthStencilBuffer> shadowMap)
	: DefferedSampleRenderPipeline(lightingPassRenderTarget, constructGeometryPass(targetRenderingGroupNameList, lightingPassRenderTarget, geometryPassDepthStencilBuffer, shadowMap), gbufferSampler, shadowMap)
{
}

DefferedSampleRenderPipeline::DefferedSampleRenderPipeline(std::shared_ptr<cg::IRenderTarget> lightingPassRenderTarget)
	: DefferedSampleRenderPipeline(lightingPassRenderTarget, cg::API::shared.graphics()->createTextureSampler())
{
}

DefferedSampleRenderPipeline::DefferedSampleRenderPipeline(std::shared_ptr<cg::IRenderTarget> lightingPassRenderTarget, std::shared_ptr<cg::ITextureSampler> gbufferSampler)
	: DefferedSampleRenderPipeline(lightingPassRenderTarget, cg::API::shared.graphics()->createDepthStencilBuffer(lightingPassRenderTarget->getSize(), cg::TextureFormat::D32_FLOAT), gbufferSampler, cg::API::shared.graphics()->createDepthStencilBuffer(lightingPassRenderTarget->getSize(), cg::TextureFormat::D32_FLOAT, lightingPassRenderTarget->getMSAASampleCount(), lightingPassRenderTarget->getMSAAQualityLevel()))
{
}

void DefferedSampleRenderPipeline::render(const cg::Scene& scene)
{
	const auto keyLight = scene.getLight<SimpleDirectionalLight>("Key");
	
	m_shadowMapRenderingPass.render(scene, keyLight->perspective);
	m_shadowMap->getDepthBufferTexture()->resolve();

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
