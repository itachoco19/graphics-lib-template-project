#pragma once
#include <GraphicsLib.hpp>
#include "VertexShaderInput.hpp"




class FullscreenQuad
{
private:
	std::shared_ptr<cg::DrawableObject> m_quad;
public:
	FullscreenQuad();
	
	std::shared_ptr<cg::DrawableObject> operator->() const noexcept;
};