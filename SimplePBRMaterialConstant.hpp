#pragma once
#include "ConstantWithImGuiComponents.hpp"
#include "ShaderConstant.hpp"





class SimplePBRMaterialConstant
	: public ConstantWithImGuiComponents
{
public:
	SimplePBRMaterialConstant();
	SimplePBRMaterialConstant(std::shared_ptr<void> pData);

	void changeColor(float r, float g, float b);
	void changeColor(const cpp::Vector3D<float>& color);

	void changeMetalness(float metalness);
	void changeRoughness(float roughness);
	void changeIOR(float ior);

	void drawImGuiComponents() override;
};