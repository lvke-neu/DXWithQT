#include "ParticleComponent.hlsli"



float4 PS(VertexOut pIn) : SV_Target
{
	//return float4(1.0f, 0.0f, 0.0f, 1.0f);
	return texColor;
}