#include "ScreenPixelFixedImage.hlsli"


VS_OUT VS(VS_IN vIn)
{

	VS_OUT output;
	output.position = mul(float4(vIn.position, 1), g_world);
	output.position = mul(output.position, g_view);
	output.position = mul(output.position, g_proj);


	return output;
}
