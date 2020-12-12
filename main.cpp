#include "DrawableObjectCreator.hpp"

#include "VertexShaderInput.hpp"
#include "ShaderConstant.hpp"

#include "SimpleDirectionalLight.hpp"
#include "SimplePointLight.hpp"

#include "ImGuiGraphicsLibDefaultInspector.hpp"

#include "ForwardSampleRenderPipeline.hpp"
#include "ForwardZPrePassSampleRenderPipeline.hpp"

#include "SimplePBRMaterialConstant.hpp"
#include "DefferedSampleRenderPipeline.hpp"




int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
#if defined(DEBUG) || defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif



	// Initialize GraphicsLib
	const auto& screenUpdater = cg::System::initialize(1500, 800, false, 16, "Sample");
	ImGui_ImplGraphicsLib_Init();



	const auto windowInfo = cg::System::getWindowInfo();
	const auto windowSize = windowInfo.getSize();
	const auto aspect = windowInfo.calcAspect();



	// Setup render target
	auto mainRenderTarget = cg::MainRenderTarget::shared.get();



	// Setup render pipeline
	std::shared_ptr<RenderPipelineWithImGuiComponents> renderPipeline;
	std::string renderingGroupName;
	try
	{
		//renderPipeline = std::make_shared<DefferedSampleRenderPipeline>(mainRenderTarget);
		//renderingGroupName = DefferedSampleRenderPipeline::targetRenderingGroupName;

		renderPipeline = std::make_shared<ForwardSampleRenderPipeline>(mainRenderTarget);
		renderingGroupName = ForwardSampleRenderPipeline::targetRenderingGroupName;

		//renderPipeline = std::make_shared<ForwardZPrePassSampleRenderPipeline>(mainRenderTarget);
		//renderingGroupName = ForwardZPrePassSampleRenderPipeline::targetRenderingGroupName;
	}
	catch (cpp::com_runtime_error e)
	{
		LogEX(e.message());
	}



	// Prepare material
	auto materialConstant = std::make_shared<SimplePBRMaterialConstant>();
	materialConstant->changeIOR(1.35f);
	materialConstant->changeMetalness(0.8f);
	materialConstant->changeRoughness(0.6f);
	materialConstant->changeColor(1.0, 0.5, 0.2);

	auto materialConstantDict = cg::Material::ConstantDict();
	materialConstantDict.emplace(cg::ShaderStage::ps, materialConstant);
	auto material = cg::Material(materialConstantDict);

	auto planeMaterial = material.clone();
	auto lucyMaterial = material.clone();
	auto buddhaMaterial = material.clone();
	auto bunnyMaterial = material.clone();

	std::dynamic_pointer_cast<SimplePBRMaterialConstant>(planeMaterial.getConstantP(cg::ShaderStage::ps))->changeColor(1.0, 1.0, 1.0);


	// Prepare objects
	auto plane = DrawableObjectCreator::createBox<vsinput::Position3Normal3>("Plane", 5.0f, 0.1f, 5.0f, planeMaterial);
	auto lucy = DrawableObjectCreator::createWavefronOBJModel<vsinput::Position3Normal3>("Lucy", "Assets/Resources/3DModel/WavefrontOBJ/Alucy.obj", lucyMaterial);
	auto buddha = DrawableObjectCreator::createWavefronOBJModel<vsinput::Position3Normal3>("Buddha", "Assets/Resources/3DModel/WavefrontOBJ/happy-buddha.obj", buddhaMaterial);
	auto bunny = DrawableObjectCreator::createWavefronOBJModel<vsinput::Position3Normal3>("Bunny", "Assets/Resources/3DModel/WavefrontOBJ/bunny.obj", bunnyMaterial);

	auto& planeTransform = plane->getTransformRef();
	auto& lucyTransform = lucy->getTransformRef();
	auto& buddhaTransform = buddha->getTransformRef();
	auto& bunnyTransform = bunny->getTransformRef();

	bunnyTransform.changeScale(0.75, 0.75, 0.75);

	planeTransform.changePosition(0.0f, -0.05f, 0.0f);
	lucyTransform.changePosition(0.0f, 0.5f, 0.0f);
	buddhaTransform.changePosition(-1.0f, 0.5f, 0.0f);
	bunnyTransform.changePosition(1.0, 0.375f, 0.0f);

	lucyTransform.changeEulerRotationAngleY(2.3);
	buddhaTransform.changeEulerRotationAngleY(-0.8);
	bunnyTransform.changeEulerRotationAngleY(3.1);


	plane->moveTo(renderingGroupName);
	lucy->moveTo(renderingGroupName);
	buddha->moveTo(renderingGroupName);
	bunny->moveTo(renderingGroupName);


	// Setup Scene
	auto scene = cg::Scene("World");

	auto mainGroup = std::make_shared<cg::DrawableObjectGroup>("MainGroup");
	mainGroup->add(plane);
	mainGroup->add(lucy);
	mainGroup->add(buddha);
	mainGroup->add(bunny);

	scene.addObjectGroup(mainGroup);



	// Setup Camera
	auto& cameraTransform = scene.camera.getTransformRef();
	cameraTransform.changePosition(0.0f, 1.0f, -2.0f);
	cameraTransform.changeCoordinateSystem(cg::CoordinateSystem::rectangular);
	cameraTransform.changeRotationMethod(cg::RotationMethod::lookAt);
	cameraTransform.changeFocusPositionLocal(0.0f, 0.0f, 0.0f);
	cameraTransform.changeUpLocal(0.0f, 1.0f, 0.0f);

	auto& cameraProjection = scene.camera.projection;
	cameraProjection.changeFov(cpp::Math::degreeToRadian(60.0f));
	cameraProjection.changeAspect(aspect);
	cameraProjection.changeNearZ(0.001f);
	cameraProjection.changeFarZ(10.0f);



	// Setup key light
	auto keyLight = std::make_shared<SimpleDirectionalLight>("Key");
	auto& keyLightCameraTransform = keyLight->perspective.getTransformRef();
	auto& keyLightCameraProjection = keyLight->perspective.projection;

	const auto keyLightDirection = cpp::Vector3D<float>(0.0f, -0.5f, 1.0f);
	auto keyLightCameraPosition = -3.0f * keyLightDirection;

	keyLight->accessToColorParam().changeColor(0.9f, 0.9f, 0.9f);

	keyLightCameraProjection.changeType(cg::ProjectionType::orthographic3D);
	keyLightCameraProjection.changeViewSize(2.5f * aspect, 2.5f);
	keyLightCameraProjection.changeNearZ(0.001f);
	keyLightCameraProjection.changeFarZ(10.0f);

	keyLightCameraTransform.changeRotationMethod(cg::RotationMethod::directionBase);
	keyLightCameraTransform.changeDirectionWorld(keyLightDirection);
	keyLightCameraTransform.changeUpWorld(0.0f, 1.0f, 0.0f);
	keyLightCameraTransform.changePosition(keyLightCameraPosition);

	scene.addLight(keyLight);



	// Setup back light
	auto pointLight = std::make_shared<SimplePointLight>("Back");
	auto& pointLightTransform = pointLight->getTransformRef();

	pointLight->accessToColorParam().changeColor(1.0f, 1.0f, 1.0f);

	auto pointLightAttenuParam = pointLight->accessToAttenuationParam();
	pointLightAttenuParam.changeConstant(1.0f);
	pointLightAttenuParam.changeLinear(0.6f);
	pointLightAttenuParam.changeQuadratic(0.3f);

	pointLightTransform.changePosition(cpp::Vector3D<float>(0.0f, 0.1f, 3.0f));

	scene.addLight(pointLight);



	// Game Loop
	CameraController cameraController;
	ImGui::GraphicsLibDefaultInspector inspector;
	while (screenUpdater->update())
	{
		ImGui_ImplGraphicsLib_NewFrame();

		renderPipeline->render(scene);

		inspector.draw(scene, cameraController, renderPipeline);

		cameraController.control(scene.camera);

		ImGui_ImplGraphicsLib_Render();
	}



	// Finalize GraphicsLib
	ImGui_ImplGraphicsLib_Shutdown();
	cg::System::finalize();
}
