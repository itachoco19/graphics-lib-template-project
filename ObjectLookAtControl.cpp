#include "ObjectLookAtControl.hpp"





void ObjectLookAtControl::execute(cg::Transform& target, float angleDelta, float movementDelta, bool shouldInitialize)
{
	const auto mousePosition = cpp::Vector2D<float>(ImGui::GetMousePos().x, ImGui::GetMousePos().y);



	const auto centerPosition = target.calcCenterWorld();
	const bool isCenterPositionChanged = centerPosition != m_preCenterPosition;

	if (shouldInitialize)
	{
		const auto focusPosition = target.calcFocusPositionWorld();

		target.changeCoordinateSystem(cg::CoordinateSystem::polar);
		target.changeRotationMethod(cg::RotationMethod::lookAt);
	
		target.changeCenterWorld(target.calcPositionWorld());
		target.changeFocusPositionWorld(focusPosition);
		target.changeRadiusPhiTheta(0.0f, 0.0f, static_cast<float>(-cpp::Math::HALF_PI));
	}
	else if (isCenterPositionChanged)
	{
		target.changeFocusPositionWorld(centerPosition);
	}



	float radius = target.calcRadius();
	if (ImGui::IsKeyDown(ImGui::GetKeyIndex(ImGuiKey_W)))
	{
		radius -= movementDelta;
	}
	if (ImGui::IsKeyDown(ImGui::GetKeyIndex(ImGuiKey_S)))
	{
		radius += movementDelta;
	}
	target.changeRadius(radius);



	if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
	{
		m_preMousePosition = mousePosition;
	}
	if (ImGui::IsMouseDragging(ImGuiMouseButton_Left) && !ImGui::IsMouseHoveringAnyWindow())
	{
		auto phiTheta = cpp::Vector2D<float>(target.calcPhi(), target.calcTheta())+(mousePosition-m_preMousePosition)*angleDelta;
		phiTheta.y = max(min(phiTheta.y, -0.000001f), static_cast<float>(-cpp::Math::PI)+0.00001f);
		target.changePhiTheta(phiTheta.x, phiTheta.y);
	}



	m_preMousePosition = mousePosition;
	m_preCenterPosition = centerPosition;
}
