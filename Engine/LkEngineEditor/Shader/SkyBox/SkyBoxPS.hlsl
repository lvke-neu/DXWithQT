#include "SkyBox.hlsli"


TextureCube g_TexCube : register(t0);
SamplerState g_SamplerState : register(s0);

float4 PS(VertexOut pIn) : SV_Target
{
	return g_TexCube.Sample(g_SamplerState, pIn.posL);
	//return float4(1,0,0,1);
}

