#include "../CommonShader.hlsli"

struct VertexIn
{
	float3 posL : POSITION;
	float3 normalL : NORMAL;
	float2 texcoord : TEXCOORD;
};

struct VertexOut
{
	float4 posH : SV_POSITION;
	float3 posW : POSITION;
	float3 normalW: NORMAL;
	float2 texcoord: TEXCOORD;
};

cbuffer WorldMatrix : register(b2)
{
	matrix g_world;
	matrix g_worldInvTranspose;
}

cbuffer  MaterialCB : register(b3)
{
	Material g_material;
}