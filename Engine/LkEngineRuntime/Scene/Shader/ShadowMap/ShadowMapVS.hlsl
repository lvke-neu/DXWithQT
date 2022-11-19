#include "ShadowMap.hlsli"


VertexOut VS(VertexIn vIn)
{
	VertexOut vOut;
	vOut.PosH = mul(float4(vIn.PosL, 1.0f), g_world);
	vOut.PosH = mul(vOut.PosH, g_view);
	vOut.PosH = mul(vOut.PosH, g_orthographiProj);
    vOut.Tex = vIn.Tex;

    return vOut;
}
