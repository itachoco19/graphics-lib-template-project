#include "SampleShadingRenderPipeline.hpp"
#include "ShaderConstant.hpp"
#include "SimplePointLight.hpp"
#include "SimpleDirectionalLight.hpp"





SampleShadingRenderPipeline::SampleShadingRenderPipeline(const TargetRenderingGroupNameList& targetRenderingGroupNameList, std::shared_ptr<cg::IDepthStencilBuffer> depthStencilBuffer, std::shared_ptr<cg::IDepthStencilTester> depthStencilTester, std::shared_ptr<cg::IDepthStencilBuffer> shadowMap, std::shared_ptr<cg::ITextureSampler> shadowMapSampler)
	: SampleShadingRenderPipeline(targetRenderingGroupNameList, cg::MainRenderTarget::shared.get(), depthStencilBuffer, depthStencilTester, shadowMap, shadowMapSampler)
{
}

SampleShadingRenderPipeline::SampleShadingRenderPipeline(const TargetRenderingGroupNameList& targetRenderingGroupNameList, std::shared_ptr<cg::IRenderTarget> renderTarget, std::shared_ptr<cg::IDepthStencilBuffer> depthStencilBuffer, std::shared_ptr<cg::IDepthStencilTester> depthStencilTester, std::shared_ptr<cg::IDepthStencilBuffer> shadowMap, std::shared_ptr<cg::ITextureSampler> shadowMapSampler)
	: RenderPipelineSRTWithImGuiComponents("Simple Shading",
		                targetRenderingGroupNameList,
		                renderTarget, 
		                depthStencilBuffer, 
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
										cg::TransformConstantBuffer::ElementBuffer::constructor<constant::TransformW_WVP_N_LWVP>
										(
											[](constant::TransformW_WVP_N_LWVP& data, const cg::Scene& s, const cg::Transform& t, const cg::Camera& c)
											{
												cg::TransformConstantBufferHelper::storeW(&data.w, t);
												cg::TransformConstantBufferHelper::storeWVP(&data.wvp, t, c);
												cg::TransformConstantBufferHelper::storeN(&data.n, t);

												const auto keyLight = std::dynamic_pointer_cast<SimpleDirectionalLight>(s.getLightDict().at("Key"));
												cg::TransformConstantBufferHelper::storeWVP(&data.lwvp, t, keyLight->perspective);
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
						depthStencilTester,
						{
							{ cg::ShaderStage::vs, std::dynamic_pointer_cast<cg::IVertexShader>(cg::ShaderPool::shared.createFromFileAndAdd(cg::ShaderStage::vs, "Position3Normal3InOut.vsh", "Position3Normal3InOut.vsh", "vs_main", "vs_4_0")) },
							{ cg::ShaderStage::ps, std::dynamic_pointer_cast<cg::IPixelShader>(cg::ShaderPool::shared.createFromFileAndAdd(cg::ShaderStage::ps, "SimpleShading.psh", "SimpleShading.psh", "ps_main", "ps_4_0")) }
						}),
						m_shadowMap(shadowMap),
						m_shadowMapSampler(shadowMapSampler)
{
	m_rasterizer = cg::API::shared.graphics()->createRasterizer(cg::CullMode::back, false, false, false, false, false, false);
	m_alphaBlender = cg::API::shared.graphics()->createAlphaBlender(cg::AlphaBlenderDescriptor());
}

void SampleShadingRenderPipeline::render(const cg::Scene& scene)
{
	const auto pixelShaderLocationDict = getDictOfShadersSetInPipeline().at(cg::ShaderStage::ps)->getResourceLocationDict();
	auto setCall = [&](const cg::Scene scene)
	{
		m_renderTarget->set(m_depthStencilBuffer);

		auto shadowMap = m_shadowMap->getDepthBufferTexture();
		if (m_shadowMap->getDepthBufferTextureMS())
		{
			shadowMap->resolve();
		}

		shadowMap->set(cg::ShaderStage::ps, pixelShaderLocationDict.at(cg::ShaderResourceType::Texture).at("shadowMap"), cg::GPUAccessFlags::R);
		m_shadowMapSampler->set(cg::ShaderStage::ps, pixelShaderLocationDict.at(cg::ShaderResourceType::TextureSampler).at("shadowMapSampler"));
	};
	auto drawCall = [&]()
	{
	};
	renderDefault(scene, setCall, drawCall);
}

void SampleShadingRenderPipeline::render()
{
}

void SampleShadingRenderPipeline::drawImGuiComponents()
{
}