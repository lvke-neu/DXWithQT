#include "FlatPixelFixedImage.hlsli"

[maxvertexcount(4)]
void GS(point VS_OUT input[1], inout TriangleStream<PS_IN> SpriteStream)
{
	//PS_IN output;

	//float viewportSizeWidth =  g_viewportSize.z;
	//float viewportSizeHeight = g_viewportSize.w;

	//float4 position = input[0].position;
	//position.x += viewportSizeWidth * position.w * 2;
	//position.y -= viewportSizeHeight * position.w * 2;

	//output.position = position;
	//output.position.x -= 50 * viewportSizeWidth * position.w;
	//output.position.y -= 50 * viewportSizeHeight * position.w;
	//output.texcoord = float2(0, 1);
	//SpriteStream.Append(output);

	//output.position = position;
	//output.position.x -= 50 * viewportSizeWidth * position.w;
	//output.position.y += 50 * viewportSizeHeight * position.w;
	//output.texcoord = float2(0, 0);
	//SpriteStream.Append(output);

	//output.position = position;
	//output.position.x += 50 * viewportSizeWidth * position.w;
	//output.position.y -= 50 * viewportSizeHeight * position.w;
	//output.texcoord = float2(1, 1);
	//SpriteStream.Append(output);

	//output.position = position;
	//output.position.x += 50 * viewportSizeWidth * position.w;
	//output.position.y += 50 * viewportSizeHeight * position.w;
	//output.texcoord = float2(1, 0);
	//SpriteStream.Append(output);

	//SpriteStream.RestartStrip();



	float viewportSizeWidth = g_viewportSize.z;
	float viewportSizeHeight = g_viewportSize.w;

	PS_IN output;
	float3 viewPos1 = mul(mul(input[0].position, g_world), g_view).xyz;
	float4 position = input[0].position;
	//position.x += 2 * viewPos1.z * g_invProj[1][1]  * viewportSizeHeight;
	//position.z -= 2 * viewPos1.z * g_invProj[1][1]  * viewportSizeHeight;

	float2 sizeMeter;
	float pixelWidth = 50.0/ 2;
	float pixelHeight = 50.0 / 2;
	//sizeMeter.x = 5;
	//sizeMeter.y = 5;
	sizeMeter.x = 2 * viewPos1.z * g_invProj[1][1] * pixelWidth * viewportSizeHeight;
	sizeMeter.y = 2 * viewPos1.z * g_invProj[1][1] * pixelHeight * viewportSizeHeight;
	//0
	output.position = position;
	output.position.x -= sizeMeter.x;
	output.position.z -= sizeMeter.y;
	output.position = mul(mul(mul(output.position, g_world), g_view), g_proj);
	output.texcoord = float2(0, 1);
	SpriteStream.Append(output);


	//1
	output.position = position;
	output.position.x -= sizeMeter.x;
	output.position.z += sizeMeter.y;
	output.position = mul(mul(mul(output.position, g_world), g_view), g_proj);
	output.texcoord = float2(0, 0);
	SpriteStream.Append(output);
	//2
	output.position = position;
	output.position.x += sizeMeter.x;
	output.position.z -= sizeMeter.y;
	output.position = mul(mul(mul(output.position, g_world), g_view), g_proj);
	output.texcoord = float2(1, 1);
	SpriteStream.Append(output);

	//3
	output.position = position;
	output.position.x += sizeMeter.x;
	output.position.z += sizeMeter.y;
	output.position = mul(mul(mul(output.position, g_world), g_view), g_proj);
	output.texcoord = float2(1, 0);
	SpriteStream.Append(output);

	SpriteStream.RestartStrip();

}