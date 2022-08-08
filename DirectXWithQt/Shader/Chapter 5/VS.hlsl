#include "Common.hlsli"


VertexOut VS(VertexIn vIn)
{
	float4 posW = mul(float4(vIn.posL, 1.0f), g_world);

	//阴影
	[flatten]
	if (g_isShadow)
	{
		posW =  mul(posW, g_shadowMatrix);
	}

	float4 posV = mul(posW, g_view);
	float4 posH = mul(posV, g_proj);


	VertexOut vOut;
	vOut.posH = posH;
	vOut.posW = posW.xyz;
	vOut.normalW = mul(vIn.normalL, (float3x3)g_worldInvTranspose);
	vOut.texcoord = vIn.texcoord;

	return vOut;
}
