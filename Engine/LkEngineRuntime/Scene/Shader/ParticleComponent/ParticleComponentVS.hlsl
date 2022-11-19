#include "ParticleComponent.hlsli"


VertexOut VS(VertexIn vIn)
{
	float4 posW = mul(float4(vIn.posL, 1.0f), g_world);
	float4 posV = mul(posW, g_view);
	float4 posH = mul(posV, g_proj);

	VertexOut vOut;
	vOut.posH = posH;

	return vOut;
}
