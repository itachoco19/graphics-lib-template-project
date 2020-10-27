#include "SimpleDirectionalLight.hpp"
#include "ShaderConstant.hpp"
#include <ThirdParty/ExtendedImGui/ImGui/imgui.h>




const std::string SimpleDirectionalLight::type = "SimpleDirectionalLight";



SimpleDirectionalLight::SimpleDirectionalLight(const std::string& name, std::shared_ptr<cg::Constant> mainConstant)
	: DirectionalLight(type, name, SimpleDirectionalLightConstant(*mainConstant), mainConstant)
{
}
SimpleDirectionalLight::SimpleDirectionalLight(const std::string& name)
	: SimpleDirectionalLight(name, std::make_shared<MainConstant>())
{
}


SimpleDirectionalLight::ColorConstant::ColorConstant(std::shared_ptr<void> rawSourceConstantRef)
	: cg::Constant(rawSourceConstantRef)
{
}

void SimpleDirectionalLight::ColorConstant::changeColor(const cpp::Vector3D<float>& color)
{
	changeColor(color.x, color.y, color.z);
}

void SimpleDirectionalLight::ColorConstant::changeColor(float r, float g, float b)
{
	tweak<constant::SimpleDirectionalLight>([&](constant::SimpleDirectionalLight& light)
	{
		light.color[0] = r;
		light.color[1] = g;
		light.color[2] = b;
	});
}

cpp::Vector3D<float> SimpleDirectionalLight::ColorConstant::getColor() const noexcept
{
	return cpp::Vector3D<float>(get<constant::SimpleDirectionalLight>().color);
}

SimpleDirectionalLight::ColorConstant SimpleDirectionalLight::accessToColorParam() const noexcept
{
	return getColorConstant<SimpleDirectionalLight::ColorConstant>();
}

SimpleDirectionalLight::MainConstant::MainConstant()
	: ConstantWithImGuiComponents(std::make_shared<constant::SimpleDirectionalLight>())
{
}

void SimpleDirectionalLight::MainConstant::drawImGuiComponents()
{
	auto p = std::reinterpret_pointer_cast<constant::SimpleDirectionalLight>(getP());
	ImGui::ColorEdit3("Color", p->color.data());
}

SimpleDirectionalLight::SimpleDirectionalLightConstant::SimpleDirectionalLightConstant(const cg::Constant& sourceConstant)
	: DirectionalLightConstant(sourceConstant)
{
}
