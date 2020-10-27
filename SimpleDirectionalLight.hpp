#pragma once
#include "ConstantWithImGuiComponents.hpp"
#include <GraphicsLib.hpp>





class SimpleDirectionalLight
	: public cg::DirectionalLight
{
public:
	const static std::string type;
private:
	class MainConstant
		: public ConstantWithImGuiComponents
	{
	public:
		MainConstant();
		virtual ~MainConstant() = default;

		void drawImGuiComponents() override;
	};
	class ColorConstant
		: public cg::Constant
	{
	public:
		ColorConstant(std::shared_ptr<void> rawSourceConstantRef);
		virtual ~ColorConstant() = default;

		void changeColor(const cpp::Vector3D<float>& color);
		void changeColor(float r, float g, float b);

		[[nodiscard]] cpp::Vector3D<float> getColor() const noexcept;
	};
	class SimpleDirectionalLightConstant
		: public cg::DirectionalLightConstant<ColorConstant>
	{
	public:
		SimpleDirectionalLightConstant(const cg::Constant& sourceConstant);
		virtual ~SimpleDirectionalLightConstant() = default;
	};
private:
	SimpleDirectionalLight(const std::string& name, std::shared_ptr<cg::Constant> mainConstant);
public:
	SimpleDirectionalLight(const std::string& name);
	virtual ~SimpleDirectionalLight() = default;

	[[nodiscard]] SimpleDirectionalLight::ColorConstant accessToColorParam() const noexcept;
};