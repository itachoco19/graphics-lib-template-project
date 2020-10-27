#include "DrawableObjectCreator.hpp"
#include "FullscreenQuad.hpp"





FullscreenQuad::FullscreenQuad()
{
	m_quad = DrawableObjectCreator::createPlane<vsinput::Position3UV2>("Fullscreen Quad", 1.0, 1.0);
}

std::shared_ptr<cg::DrawableObject> FullscreenQuad::operator->() const noexcept
{
	return m_quad;
}
