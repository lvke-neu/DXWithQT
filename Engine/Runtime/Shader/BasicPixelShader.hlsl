#include "Basic.hlsli"

Texture2D g_texture : register(t0);
SamplerState g_samplerState : register (s0);

float4 main(VsOut pIn) : SV_Target
{
	
	return g_texture.Sample(g_samplerState, pIn.uv);
}