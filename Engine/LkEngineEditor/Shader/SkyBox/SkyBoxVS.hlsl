#include "SkyBox.hlsli"


VertexOut VS(VertexIn vIn)
{
	float4 posW = mul(float4(vIn.posL, 1.0f), g_world);
	//float4 posW = float4(vIn.posL, 1.0f);
	float4 posV = mul(posW, g_view);
	float4 posH = mul(posV, g_proj);

	VertexOut vOut;
	vOut.posH = posH.xyww;
	vOut.posW = posW.xyz;
	vOut.normalW = mul(vIn.normalL, (float3x3)g_worldInvTranspose);
	vOut.texcoord = vIn.texcoord;
	vOut.posL = vIn.posL;

	return vOut;
}
