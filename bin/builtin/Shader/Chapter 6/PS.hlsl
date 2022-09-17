#include "Common.hlsli"


Texture2D g_Tex : register(t0);
SamplerState g_SamplerState : register(s0);
float4 PS(VertexOut pIn) : SV_Target
{
	return  g_Tex.Sample(g_SamplerState, pIn.texcoord);

}

