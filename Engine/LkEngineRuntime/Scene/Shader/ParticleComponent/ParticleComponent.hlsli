#include "../CommonShader.hlsli"

struct VertexIn
{
	float3 posL : POSITION;
};

struct VertexOut
{
	float4 posH : SV_POSITION;
};

cbuffer WorldMatrix : register(b3)
{
	matrix g_world;
	matrix g_worldInvTranspose;
}

cbuffer UseTexOrColor : register(b5)
{
	float4 texColor;
	float3 padd;
	float isUseTex;
}
