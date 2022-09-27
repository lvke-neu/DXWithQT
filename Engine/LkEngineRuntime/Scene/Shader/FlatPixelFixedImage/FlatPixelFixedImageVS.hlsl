#include "FlatPixelFixedImage.hlsli"


VS_OUT VS(VS_IN vIn)
{

	VS_OUT output;

	output.position = float4(vIn.position, 1);

	return output;
}
