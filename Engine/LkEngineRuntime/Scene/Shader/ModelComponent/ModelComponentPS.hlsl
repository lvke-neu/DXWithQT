#include "ModelComponent.hlsli"

Texture2D g_Tex : register(t0);
SamplerState g_SamplerState : register(s0);

float4 PS(VertexOut pIn) : SV_Target
{
	float4 color = g_Tex.Sample(g_SamplerState, pIn.texcoord);
	clip(color.a - 0.05f);

	//return float4(g_viewportSize.x, 0, 0, 1);
	return color;
}