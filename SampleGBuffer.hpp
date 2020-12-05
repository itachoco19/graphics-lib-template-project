#pragma once
#include <GraphicsLib.hpp>




class SampleGBuffer
	: public cg::GBuffer
{
public:
	inline static const std::string BaseColorRoughness = "BaseColor+Roughness";
	inline static const std::string NormalMetalness    = "Normal+Metalness";
	inline static const std::string IOR                = "IOR";
	inline static const std::string Depth              = "Depth";
	inline static const std::string ShadowMap          = "ShadowMap";
public:
	SampleGBuffer(std::shared_ptr<cg::ITexture2D> baseColorRoughness, std::shared_ptr<cg::ITexture2D> normalMetalness, std::shared_ptr<cg::ITexture2D> ior, std::shared_ptr<cg::ITexture2D> depth, std::shared_ptr<cg::ITexture2D> shadowMap);
	virtual ~SampleGBuffer() = default;
};