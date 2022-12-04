#include "CommonShader.hlsli"

VsOut main(VsIn vIn)
{
	VsOut vOut;
	vOut.pos = mul(float4(vIn.pos, 1.0f), g_worldMatrix);
	vOut.pos = mul(vOut.pos, g_viewMatrix);
	vOut.pos = mul(vOut.pos, g_projMatrix);
	vOut.uv = vIn.uv;

	return vOut;
}