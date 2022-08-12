#include "Common.hlsli"


VertexOut VS(VertexIn vIn)
{
	float4 posW = mul(float4(vIn.posL, 1.0f), g_world);

	float3 normalW = mul(vIn.normalL, (float3x3)g_worldInvTranspose);

	[flatten]
	if (g_isEnableReflec)
	{
		posW = mul(posW, g_reflectionMatrix);
		normalW = mul(normalW, (float3x3)g_reflectionMatrix);
	}

	float4 posV = mul(posW, g_view);
	float4 posH = mul(posV, g_proj);
	VertexOut vOut;
	vOut.posH = posH;
	vOut.posW = posW.xyz;
	vOut.normalW = normalW;
	vOut.texcoord = vIn.texcoord;

	return vOut;
}
