#pragma once
#include <GraphicsLib.hpp>





class ObjectFreeLookControl
{
private:
	cpp::Vector2D<float> m_preMousePosition;
public:
	void execute(cg::Transform& target, float angleDeltaRadian);
};