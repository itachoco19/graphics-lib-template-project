#pragma once

#include "ShaderConstant.h"



namespace constant
{
	using precision_ = float;
	using array4_ = cpp::Array4<precision_>;
	using array3_ = cpp::Array3<precision_>;
	using array2_ = cpp::Array2<precision_>;

	using float3x4 = DirectX::XMFLOAT3X4;
	using float3x3 = DirectX::XMFLOAT3X3;

	using float4x4 = DirectX::XMFLOAT4X4;
	using float4x3 = DirectX::XMFLOAT4X3;

	using float4_16byte = array4_;

	using float3_16byte = array4_;
	using float3_12byte = array3_;
	
	using float2_16byte = array4_;
	using float2_12byte = array3_;
	using float2_8byte  = array2_;
	
	using float1_16byte = array4_;
	using float1_12byte = array3_;
	using float1_8byte  = array2_;
	using float1_4byte  = precision_;

	


	DEFINE_SHADER_CONSTANT_C();
}
