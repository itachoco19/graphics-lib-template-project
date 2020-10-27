#include "VertexShaderInput.hlsl"



struct VSOutput
{
	float4 position : SV_POSITION;
	float2 uv : TEXCOORD0;
};



VSOutput vs_main(Position3UV2 input)
{
	VSOutput output;

	output.position = float4(float3(input.position.x, -input.position.y, input.position.z)*2.0, 1.0);
	output.uv = input.uv;

	return output;
}
