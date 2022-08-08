#include "Common.hlsli"


VertexOut VS(VertexIn vIn)
{
	VertexOut vOut;
	vOut.posH = float4(vIn.posL, 1.0f);
	vOut.texcoord = vIn.texcoord;

	return vOut;
}
