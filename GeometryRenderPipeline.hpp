#pragma once
#include "RenderPipelineMRTWithImGuiComponents.hpp"
#include "ShaderConstant.hpp"





class GeometryRenderPipeline
	: public RenderPipelineMRTWithImGuiComponents
{
private:
	AdditionalSetCallScene m_additionalSetCall;
public:
	GeometryRenderPipeline(const std::string& name, const TargetRenderingGroupNameList& targetRenderingGroupNameList, std::shared_ptr<cg::MaterialConstantBuffer> materialConstantBuffer, std::shared_ptr<cg::TransformConstantBuffer> transformConstantBuffer, const cg::RasterizationBasedRenderPipeline::ShaderDict& shaderDict, AdditionalSetCallScene additionalSetCall = [](const cg::Scene& scene) {});
	GeometryRenderPipeline(const std::string& name, const TargetRenderingGroupNameList& targetRenderingGroupNameList, std::shared_ptr<cg::MaterialConstantBuffer> materialConstantBuffer, std::shared_ptr<cg::TransformConstantBuffer> transformConstantBuffer, std::shared_ptr<cg::IDepthStencilTester> depthTesterLessFunction, const cg::RasterizationBasedRenderPipeline::ShaderDict& shaderDict, AdditionalSetCallScene additionalSetCall = [](const cg::Scene& scene) {});
	virtual ~GeometryRenderPipeline() = default;

	void render(const cg::Scene& scene, const cg::Camera& customCamera);
	void render(const cg::Scene& scene) override;
	void render() override;

	void initializeMultipleRenderTarget(std::shared_ptr<cg::IMultipleRenderTarget> mrt);
	void initializeDepthStencilBuffer(std::shared_ptr<cg::IDepthStencilBuffer> depthStenciBuffer);

	void drawImGuiComponents() override;
};





#define DEFINE_GEOMETRY_RENDER_PIPELINE_(NAME)\
	class NAME##GeometryRenderPipeline\
		: public GeometryRenderPipeline\
	{\
	public:\
		NAME##GeometryRenderPipeline(const TargetRenderingGroupNameList& targetRenderingGroupNameList, std::shared_ptr<cg::IMultipleRenderTarget> mrt, std::shared_ptr<cg::IDepthStencilBuffer> depthStencilBuffer, std::shared_ptr<cg::MaterialConstantBuffer> materialConstantBuffer)\
			: GeometryRenderPipeline("Geometry Render Pipeline",\
			  targetRenderingGroupNameList,\
              materialConstantBuffer,\
			  std::make_shared<cg::TransformConstantBuffer>\
              (\
				  cg::TransformConstantBuffer::BufferDict\
				  {\
					  {\
					      cg::ShaderStage::vs,\
\
						  std::make_shared<cg::TransformConstantBuffer::ElementBuffer>\
						  (\
							  cg::TransformConstantBuffer::ElementBuffer::constructor<constant::TransformW_VP_N>\
							  (\
								  [](constant::TransformW_VP_N& data, const cg::Scene& s, const cg::Transform& t, const cg::Camera& c)\
								  {\
									  cg::TransformConstantBufferHelper::storeW(&data.w, t);\
									  cg::TransformConstantBufferHelper::storeVP(&data.vp, c);\
									  cg::TransformConstantBufferHelper::storeN(&data.n, t);\
								  }\
							  )\
						  )\
					  }\
				  }\
              ),\
              { { cg::ShaderStage::vs, std::dynamic_pointer_cast<cg::IVertexShader>(cg::ShaderPool::shared.createFromFileAndAdd(cg::ShaderStage::vs, "DepthPass.vsh/vs_main_"#NAME"", "DepthPass.vsh", "vs_main_"#NAME"", "vs_4_0")) } })\
		{\
		}\
	}

DEFINE_GEOMETRY_RENDER_PIPELINE_(Position3);
DEFINE_GEOMETRY_RENDER_PIPELINE_(Position3Normal3);
DEFINE_GEOMETRY_RENDER_PIPELINE_(Position3Normal4);
DEFINE_GEOMETRY_RENDER_PIPELINE_(Position3UV2);
DEFINE_GEOMETRY_RENDER_PIPELINE_(Position3UV2Normal3);
DEFINE_GEOMETRY_RENDER_PIPELINE_(Position3UV2Normal4);

DEFINE_GEOMETRY_RENDER_PIPELINE_(Position4);
DEFINE_GEOMETRY_RENDER_PIPELINE_(Position4Normal3);
DEFINE_GEOMETRY_RENDER_PIPELINE_(Position4Normal4);
DEFINE_GEOMETRY_RENDER_PIPELINE_(Position4UV2);
DEFINE_GEOMETRY_RENDER_PIPELINE_(Position4UV2Normal3);
DEFINE_GEOMETRY_RENDER_PIPELINE_(Position4UV2Normal4);