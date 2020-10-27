#include "ImGuiTransformInspector.hpp"
#include <GraphicsLib.hpp>





namespace ImGui
{ 
	void TransformInspector(cg::Transform& transform)
	{
		constexpr const char* itemEulerRotation         = "Euler Rotation";
		constexpr const char* itemQuaternionRotation    = "Quaternion Rotation";
		constexpr const char* itemLookAtRotation        = "LookAt Rotation";
		constexpr const char* itemPolarRotation         = "Polar Rotation";
		constexpr const char* itemDirectionBaseRotation = "Direction Base Rotation";
		static const std::vector<std::string> rotationMethodList = { itemEulerRotation, itemQuaternionRotation, itemLookAtRotation, itemPolarRotation, itemDirectionBaseRotation };

		constexpr const char* itemRectangularCoordinateSystem = "Rectangular Coordinate System";
		constexpr const char* itemPolarCoordinateSystem = "Polar Coordinate System";
		static const std::vector<std::string> coordinateSystemList = { itemRectangularCoordinateSystem, itemPolarCoordinateSystem };



		std::string previewItem = "";
		int previewItemIndex = -1;
		switch (transform.getCoordinateSystem())
		{
		case cg::CoordinateSystem::rectangular:
			previewItem = itemRectangularCoordinateSystem;
			break;
		case cg::CoordinateSystem::polar:
			previewItem = itemPolarCoordinateSystem;
			break;
		}
		ImGui::Combo("Coordinate System", coordinateSystemList, previewItem, previewItemIndex);
		const auto coordinateSystem = previewItem;





		if (coordinateSystem == itemRectangularCoordinateSystem)
		{
			transform.changeCoordinateSystem(cg::CoordinateSystem::rectangular);
			transform.tweakPosition([](cpp::Vector3D<float>& p)
			{
				ImGui::InputVector3D("Position", p);
			});
		}
		else if (coordinateSystem == itemPolarCoordinateSystem)
		{
			transform.changeCoordinateSystem(cg::CoordinateSystem::polar);
			transform.tweakCenterLocal([](cpp::Vector3D<float>& c)
			{
				ImGui::InputVector3D("Center", c);
			});
			transform.tweakRadius([](float& r) 
			{
				ImGui::InputFloat("Radius", &r);
			});
			transform.tweakPhi([](float& p) 
			{
				ImGui::InputFloat("Phi", &p);
			});
			transform.tweakTheta([](float& t) 
			{
				ImGui::InputFloat("Theta", &t);
			});
		}



		previewItem = "";
		previewItemIndex = -1;
		switch (transform.getRotationMethod())
		{
		case cg::RotationMethod::euler:
			previewItem = itemEulerRotation;
			break;
		case cg::RotationMethod::quaternion:
			previewItem = itemQuaternionRotation;
			break;
		case cg::RotationMethod::lookAt:
			previewItem = itemLookAtRotation;
			break;
		case cg::RotationMethod::polar:
			previewItem = itemPolarRotation;
			break;
		case cg::RotationMethod::directionBase:
			previewItem = itemDirectionBaseRotation;
			break;
		}
		ImGui::Combo("Rotation Method", rotationMethodList, previewItem, previewItemIndex);
		const auto rotationMethod = previewItem;



		if (rotationMethod == itemEulerRotation)
		{
			transform.changeRotationMethod(cg::RotationMethod::euler);
			transform.tweakEulerRotationAngles([](cpp::Vector3D<float>& a)
			{
				ImGui::InputVector3D("Angles", a);
			});
		}
		else if (rotationMethod == itemQuaternionRotation)
		{
			transform.changeRotationMethod(cg::RotationMethod::quaternion);
			transform.tweakRotationAxisLocal([](cpp::Vector3D<float>& a)
			{	
				ImGui::InputVector3D("Axis", a);
			});
			transform.tweakQuaternionRotationAngle([](float& a)
			{
				ImGui::InputFloat("Angle", &a);
			});
		}
		else if (rotationMethod == itemLookAtRotation)
		{
			transform.changeRotationMethod(cg::RotationMethod::lookAt);
			transform.tweakFocusPositionLocal([](cpp::Vector3D<float>& l)
			{
				ImGui::InputVector3D("LookAt", l);
			});
			transform.tweakUpLocal([](cpp::Vector3D<float>& u)
			{
				ImGui::InputVector3D("Up", u);
			});
		}
		else if (rotationMethod == itemPolarRotation)
		{
			transform.changeRotationMethod(cg::RotationMethod::polar);
			transform.tweakPolarRotationAnglePhi([](float& p)
			{
				ImGui::InputFloat("Phi", &p);
			});
			transform.tweakPolarRotationAngleTheta([](float& t)
			{
				ImGui::InputFloat("Theta", &t);
			});
			transform.tweakUpLocal([](cpp::Vector3D<float>& u)
			{
				ImGui::InputVector3D("Up", u);
			});
		}
		else if (rotationMethod == itemDirectionBaseRotation)
		{
			transform.changeRotationMethod(cg::RotationMethod::directionBase);
			transform.tweakDirectionLocal([](cpp::Vector3D<float>& d)
			{
				ImGui::InputVector3D("Direction", d);
			});
			transform.tweakUpLocal([](cpp::Vector3D<float>& u)
			{
				ImGui::InputVector3D("Up", u);
			});
		}



		transform.tweakScale([](cpp::Vector3D<float>& s)
		{
			ImGui::InputVector3D("Scale", s);
		});
	}
}
