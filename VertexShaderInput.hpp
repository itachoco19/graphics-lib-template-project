#pragma once
#include "VertexShaderInput.h"





namespace vsinput
{
	using precision_ = float;

	using float4 = cpp::Array4<precision_>;
	using float3 = cpp::Array3<precision_>;
	using float2 = cpp::Array2<precision_>;
	using float1 = precision_;



	DEFINE_VS_INPUT();
}
