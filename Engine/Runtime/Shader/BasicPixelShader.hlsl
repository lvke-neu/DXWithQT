#include "Basic.hlsli"

Texture2D g_texture : register(t0);
SamplerState g_samplerState : register (s0);

float4 main(VsOut pIn) : SV_Target
{
	float4 color = g_texture.Sample(g_samplerState, pIn.uv);
	//color.a = 0.5f;
	return color;
}