#include "Common.hlsli"


VertexOut2 VS(VertexIn2 vIn)
{
	float4 posW = mul(float4(vIn.posL, 1.0f), g_world);
	float4 posV = mul(posW, g_view);
	float4 posH = mul(posV, g_proj);

	VertexOut2 vOut;
	vOut.posH = posH;
	vOut.posW = posW.xyz;
	vOut.normalW = mul(vIn.normalL, (float3x3)g_worldInvTranspose);
	vOut.tangentW = mul(vIn.tangentL, g_world);
	vOut.texcoord = vIn.texcoord;

	return vOut;
}
