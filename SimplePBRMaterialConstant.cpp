#include "SimplePBRMaterialConstant.hpp"





SimplePBRMaterialConstant::SimplePBRMaterialConstant()
	: ConstantWithImGuiComponents(std::make_shared<constant::SimplePBRMaterial>())
{
}

SimplePBRMaterialConstant::SimplePBRMaterialConstant(std::shared_ptr<void> pData)
	: ConstantWithImGuiComponents(pData)
{
}



void SimplePBRMaterialConstant::changeColor(float r, float g, float b)
{
	tweak<constant::SimplePBRMaterial>([=](constant::SimplePBRMaterial& mat)
	{
		mat.color[0] = r;
		mat.color[1] = g;
		mat.color[2] = b;
	});
}
void SimplePBRMaterialConstant::changeColor(const cpp::Vector3D<float>& color)
{
	changeColor(color.x, color.y, color.z);
}



void SimplePBRMaterialConstant::changeMetalness(float metalness)
{
	tweak<constant::SimplePBRMaterial>([=](constant::SimplePBRMaterial& mat)
	{
		mat.metalness = metalness;
	});
}



void SimplePBRMaterialConstant::changeRoughness(float roughness)
{
	tweak<constant::SimplePBRMaterial>([=](constant::SimplePBRMaterial& mat)
	{
		mat.roughness = roughness;
	});
}



void SimplePBRMaterialConstant::changeIOR(float ior)
{
	tweak<constant::SimplePBRMaterial>([=](constant::SimplePBRMaterial& mat)
	{
		mat.ior[0] = ior;
	});
}



void SimplePBRMaterialConstant::drawImGuiComponents()
{
	tweak<constant::SimplePBRMaterial>([=](constant::SimplePBRMaterial& mat)
	{
		ImGui::ColorEdit3("Color", mat.color.data());
		ImGui::SliderFloat("Roughness", &mat.roughness, 0.0, 1.0);
		ImGui::SliderFloat("Metalness", &mat.metalness, 0.0, 1.0);
		ImGui::InputFloat("IOR", mat.ior.data());
	});
}