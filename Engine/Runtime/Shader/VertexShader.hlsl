#include "CommonShader.hlsli"

VsOut main(VsIn vIn)
{
	VsOut vOut;
	vOut.pos = float4(vIn.pos, 0.0f, 1.0f);
	vOut.uv = vIn.uv;

	return vOut;
}