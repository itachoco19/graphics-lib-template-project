#include "ObjectWASDControl.hpp"





void ObjectWASDControl::execute(cg::Transform& target, float movementDelta)
{
	target.changeCoordinateSystem(cg::CoordinateSystem::rectangular);



	cpp::Vector3D<float> delta;
	if (ImGui::IsKeyDown(ImGui::GetKeyIndex(ImGuiKey_W)))
	{
		if (ImGui::IsKeyDown(ImGui::GetKeyIndex(ImGuiKey_Shift)))
		{
			delta = target.calcUpWorld();
		}
		else
		{
			delta = target.calcForwardWorld();
		}
	}
	if (ImGui::IsKeyDown(ImGui::GetKeyIndex(ImGuiKey_D)))
	{
		delta = target.calcSideWorld();
	}
	if (ImGui::IsKeyDown(ImGui::GetKeyIndex(ImGuiKey_S)))
	{
		if (ImGui::IsKeyDown(ImGui::GetKeyIndex(ImGuiKey_Shift)))
		{
			delta = -target.calcUpWorld();
		}
		else
		{
			delta = -target.calcForwardWorld();
		}
	}
	if (ImGui::IsKeyDown(ImGui::GetKeyIndex(ImGuiKey_A)))
	{
		delta = -target.calcSideWorld();
	}



	target.translate(delta*movementDelta);
}
