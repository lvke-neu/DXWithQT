#include "../CommonShader.hlsli"

struct VS_IN
{
	float3 position : POSITION;
};

struct VS_OUT
{
	float4 position : SV_POSITION;
};

struct PS_IN
{
	float4 position : SV_POSITION;
	float2 texcoord : TEXCOORD;
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