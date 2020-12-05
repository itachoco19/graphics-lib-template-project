#include "SampleGBuffer.hpp"

SampleGBuffer::SampleGBuffer(std::shared_ptr<cg::ITexture2D> baseColorRoughness, std::shared_ptr<cg::ITexture2D> normalMetalness, std::shared_ptr<cg::ITexture2D> ior, std::shared_ptr<cg::ITexture2D> depth, std::shared_ptr<cg::ITexture2D> shadowMap)
	: GBuffer
	  (
	      {
			  cg::GBufferContent(SampleGBuffer::BaseColorRoughness, baseColorRoughness),
			  cg::GBufferContent(SampleGBuffer::NormalMetalness,    normalMetalness),
			  cg::GBufferContent(SampleGBuffer::IOR,                ior),
			  cg::GBufferContent(SampleGBuffer::Depth,              depth),
			  cg::GBufferContent(SampleGBuffer::ShadowMap,          shadowMap)
		  }
	  )
{
}
