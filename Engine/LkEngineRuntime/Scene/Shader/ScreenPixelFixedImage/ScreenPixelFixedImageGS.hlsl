#include "ScreenPixelFixedImage.hlsli"

[maxvertexcount(4)]
void GS(point VS_OUT input[1], inout TriangleStream<PS_IN> SpriteStream)
{
	PS_IN output;

	float viewportSizeWidth =  g_viewportSize.z;
	float viewportSizeHeight = g_viewportSize.w;

	float4 position = input[0].position;
	position.x += viewportSizeWidth * position.w * 2;
	position.y -= viewportSizeHeight * position.w * 2;

	output.position = position;
	output.position.x -= 50 * viewportSizeWidth * position.w;
	output.position.y -= 50 * viewportSizeHeight * position.w;
	output.texcoord = float2(0, 1);
	SpriteStream.Append(output);

	output.position = position;
	output.position.x -= 50 * viewportSizeWidth * position.w;
	output.position.y += 50 * viewportSizeHeight * position.w;
	output.texcoord = float2(0, 0);
	SpriteStream.Append(output);

	output.position = position;
	output.position.x += 50 * viewportSizeWidth * position.w;
	output.position.y -= 50 * viewportSizeHeight * position.w;
	output.texcoord = float2(1, 1);
	SpriteStream.Append(output);

	output.position = position;
	output.position.x += 50 * viewportSizeWidth * position.w;
	output.position.y += 50 * viewportSizeHeight * position.w;
	output.texcoord = float2(1, 0);
	SpriteStream.Append(output);

	SpriteStream.RestartStrip();

}