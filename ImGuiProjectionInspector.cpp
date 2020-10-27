#include "ImGuiProjectionInspector.hpp"
#include <GraphicsLib.hpp>





namespace ImGui
{ 
	void ProjectionInspector(cg::Projection& projection)
	{
		constexpr const char* itemPerspective = "Perspective";
		constexpr const char* itemOrthographic2D = "Orthographic2D";
		constexpr const char* itemOrthographic3D = "Orthographic3D";
		static const std::vector<std::string> itemList = { itemPerspective, itemOrthographic2D, itemOrthographic3D };



		std::string previewItem = "";
		int previewItemIndex = -1;
		switch (projection.getType())
		{
		case cg::ProjectionType::perspective:
			previewItem = itemPerspective;
			break;
		case cg::ProjectionType::orthographic2D:
			previewItem = itemOrthographic2D;
			break;
		case cg::ProjectionType::orthographic3D:
			previewItem = itemOrthographic3D;
			break;
		}
		ImGui::Combo("Projection Type", itemList, previewItem, previewItemIndex);



		if (previewItem == itemPerspective)
		{
			projection.changeType(cg::ProjectionType::perspective);
			projection.tweakFov([](float& f)
			{
				ImGui::InputFloat("Fov", &f);
			});
			projection.tweakNearZ([](float& z)
			{
				ImGui::InputFloat("Near Z", &z);
			});
			projection.tweakFarZ([](float& z)
			{
				ImGui::InputFloat("Far Z", &z);
			});
		}
		else if (previewItem == itemOrthographic2D)
		{
			projection.changeType(cg::ProjectionType::orthographic2D);
			projection.tweakLowerLeft([](cpp::Vector2D<float>& l)
			{
				ImGui::InputVector2D("Lower Left", l);
			});
			projection.tweakUpperRight([](cpp::Vector2D<float>& u)
			{
				ImGui::InputVector2D("Upper Right", u);
			});
		}
		else if (previewItem == itemOrthographic3D)
		{
			projection.changeType(cg::ProjectionType::orthographic3D);
			projection.tweakViewSize([](cpp::Vector2D<float>& s)
			{
				ImGui::InputVector2D("View Size", s);
			});
			projection.tweakNearZ([](float& z)
			{
				ImGui::InputFloat("Near Z", &z);
			});
			projection.tweakFarZ([](float& z)
			{
				ImGui::InputFloat("Far Z", &z);
			});
		}
	}
}