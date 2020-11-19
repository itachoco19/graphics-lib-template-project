#include "VertexShaderInput.hlsl"
#include "ShaderConstant.hlsl"





Define_TransformW_WVP_N_LWVP_HLSL(0);

struct VSOutput
{
	float4 position:   SV_POSITION;
	float3 positionW:  TEXCOORD1;
	float3 normal:     TEXCOORD2;
	float4 lpPosition: TEXCOORD3;
};

VSOutput vs_main(Position3Normal3 input)
{
	VSOutput output;

	output.positionW = mul(float4(input.position, 1.0), w);
	output.position = mul(float4(input.position, 1.0), wvp);
	output.normal = normalize(mul(float4(input.normal, 0.0), n).xyz);
	output.lpPosition = mul(float4(input.position, 1.0), lwvp);

	/*
	float4 lpWVP = mul(float4(input.position, 1.0), lwvp);
	lpWVP.xyz /= lpWVP.w;
	output.shadowUVZ.xy = float2(lpWVP.x*0.5+0.5, -lpWVP.y*0.5+0.5);
	output.shadowUVZ.z = lpWVP.z;
	*/

	return output;
}
