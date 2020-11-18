#pragma once
#include "VertexShaderInput.hlsl"
#include "ShaderConstant.hlsl"





Define_TransformWVP_N_HLSL(0);

struct VSOutput
{
	float4 position: SV_POSITION;
	float3 normal:   TEXCOORD0;
};

VSOutput vs_main(Position3Normal3 input)
{
	VSOutput output;

	output.position = mul(float4(input.position, 1.0), wvp);
	output.normal   = normalize(mul(float4(input.normal, 0.0), n).xyz);

	return output;
}