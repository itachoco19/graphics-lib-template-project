#pragma once
#include <GraphicsLib.hpp>
#include "ShaderConstant.hpp"
#include "ConstantWithImGuiComponents.hpp"




class SimplePointLight
	: public cg::PointLight
{
public:
	const static std::string type;
private:
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
	class AttenuationConstant
		: public cg::Constant
	{
	public:
		AttenuationConstant(std::shared_ptr<void> rawSourceConstantRef);
		virtual ~AttenuationConstant() = default;

		void changeQuadratic(float quadratic);
		void changeLinear(float linear);
		void changeConstant(float constant);

		[[nodiscard]] float getQuadratic() const noexcept;
		[[nodiscard]] float getLinear() const noexcept;
		[[nodiscard]] float getConstant() const noexcept;
	};
	class SimplePointLightConstant
		: public cg::PointLightConstant<ColorConstant, AttenuationConstant>
	{
	public:
		SimplePointLightConstant(const cg::Constant sourceConstant);
		virtual ~SimplePointLightConstant() = default;
	};

	class MainConstant
		: public ConstantWithImGuiComponents
	{
	public:
		MainConstant();
		virtual ~MainConstant() = default;

		void drawImGuiComponents() override;
	};
private:
	SimplePointLight(const std::string& name, const std::shared_ptr<MainConstant>& mainConstant);
public:
	SimplePointLight(const std::string& name);

	[[nodiscard]] SimplePointLight::ColorConstant accessToColorParam() const noexcept;
	[[nodiscard]] SimplePointLight::AttenuationConstant accessToAttenuationParam() const noexcept;
};