#pragma once
#include <GraphicsLib.hpp>





class ObjectWASDControl
{
public:
	void execute(cg::Transform& target, float movementDelta);
};