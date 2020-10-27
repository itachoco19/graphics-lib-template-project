#pragma once
#include <GraphicsLib.hpp>





class ObjectLookAtControl
{
private:
	cpp::Vector2D<float> m_preMousePosition;
	cpp::Vector3D<float> m_preCenterPosition;
public:
	void execute(cg::Transform& target, float angleDelta, float movementDelta, bool shouldInitialize);
};