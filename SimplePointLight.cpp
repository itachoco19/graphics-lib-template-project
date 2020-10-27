#include "SimplePointLight.hpp"





const std::string SimplePointLight::type = "SimplePointLight";



SimplePointLight::SimplePointLight(const std::string& name, const std::shared_ptr<MainConstant>& mainConstant)
    : PointLight(type, name, SimplePointLightConstant(*mainConstant), mainConstant)
{
}
SimplePointLight::SimplePointLight(const std::string& name)
    : SimplePointLight(name, std::make_shared<MainConstant>())
{
}
SimplePointLight::ColorConstant SimplePointLight::accessToColorParam() const noexcept
{
    return getColorConstant<ColorConstant>();
}
SimplePointLight::AttenuationConstant SimplePointLight::accessToAttenuationParam() const noexcept
{
    return getAttenuationConstant<AttenuationConstant>();
}



SimplePointLight::ColorConstant::ColorConstant(std::shared_ptr<void> rawConstantRef)
    : cg::Constant(rawConstantRef)
{

}
void SimplePointLight::ColorConstant::changeColor(const cpp::Vector3D<float>& color)
{
    changeColor(color.x, color.y, color.z);
}
void SimplePointLight::ColorConstant::changeColor(float r, float g, float b)
{
    tweak<constant::SimplePointLight>([=](constant::SimplePointLight& light)
    {
        light.color[0] = r;
        light.color[1] = g;
        light.color[2] = b;
    });
}
cpp::Vector3D<float> SimplePointLight::ColorConstant::getColor() const noexcept
{
    return cpp::Vector3D<float>(get<constant::SimplePointLight>().color);
}



SimplePointLight::AttenuationConstant::AttenuationConstant(std::shared_ptr<void> rawConstantRef)
    : cg::Constant(rawConstantRef)
{
}
void SimplePointLight::AttenuationConstant::changeQuadratic(float quadratic)
{
    tweak<constant::SimplePointLight>([=](constant::SimplePointLight& light)
    {
        light.Kclq[0] = quadratic;
    });
}
void SimplePointLight::AttenuationConstant::changeLinear(float linear)
{
    tweak<constant::SimplePointLight>([=](constant::SimplePointLight& light)
    {
        light.Kclq[1] = linear;
    });
}
void SimplePointLight::AttenuationConstant::changeConstant(float constant)
{
    tweak<constant::SimplePointLight>([=](constant::SimplePointLight& light)
    {
        light.Kclq[2] = constant;
    });
}
float SimplePointLight::AttenuationConstant::getQuadratic() const noexcept
{
    return get<constant::SimplePointLight>().Kclq[2];
}
float SimplePointLight::AttenuationConstant::getLinear() const noexcept
{
    return get<constant::SimplePointLight>().Kclq[1];
}
float SimplePointLight::AttenuationConstant::getConstant() const noexcept
{
    return get<constant::SimplePointLight>().Kclq[0];
}



SimplePointLight::SimplePointLightConstant::SimplePointLightConstant(const cg::Constant sourceConstant)
    : PointLightConstant(sourceConstant)
{
}



SimplePointLight::MainConstant::MainConstant()
    : ConstantWithImGuiComponents(std::make_shared<constant::SimplePointLight>())
{
} 
void SimplePointLight::MainConstant::drawImGuiComponents()
{
    auto p = std::reinterpret_pointer_cast<constant::SimplePointLight>(getP());
    ImGui::ColorEdit3("color", p->color.data());
    ImGui::InputFloat("Kc", &p->Kclq[0], 0.0, 1.0);
    ImGui::InputFloat("Kl", &p->Kclq[1], 0.0, 1.0);
    ImGui::InputFloat("Kq", &p->Kclq[2], 0.0, 1.0);
}
