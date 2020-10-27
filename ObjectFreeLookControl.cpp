#include "ObjectFreeLookControl.hpp"





void ObjectFreeLookControl::execute(cg::Transform& target, float angleDeltaRadian)
{
	const auto imguiMousePosition = ImGui::GetMousePos();
	const auto mousePosition = cpp::Vector2D<float>(imguiMousePosition.x, imguiMousePosition.y);



	target.changeRotationMethod(cg::RotationMethod::directionBase);



	if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
	{
		m_preMousePosition = mousePosition;
	}
	if (ImGui::IsMouseDragging(ImGuiMouseButton_Left) && !ImGui::IsMouseHoveringAnyWindow())
	{
		const auto side = target.calcSideWorld();
		const auto up = target.calcUpWorld();
		const auto forward = target.calcForwardWorld();

		const auto delta = (mousePosition-m_preMousePosition)*angleDeltaRadian;
			
		const auto rotY = DirectX::XMMatrixRotationAxis(DirectX::XMVectorSet(up.x, up.y, up.z, 0.0), delta.x);
		const auto rotX = DirectX::XMMatrixRotationAxis(DirectX::XMVectorSet(side.x, side.y, side.z, 0.0), delta.y);

		DirectX::XMFLOAT3 newDirection;
		DirectX::XMStoreFloat3(&newDirection, DirectX::XMVector4Transform(DirectX::XMVector4Transform(DirectX::XMVectorSet(forward.x, forward.y, forward.z, 1.0), rotX), rotY));
			
		target.changeUpWorld(up);
		target.changeDirectionWorld(newDirection.x, newDirection.y, newDirection.z);
	}



	m_preMousePosition = mousePosition;
}
