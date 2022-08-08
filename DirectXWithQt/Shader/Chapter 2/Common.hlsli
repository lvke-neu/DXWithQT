#include "LightHelper.hlsli"


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

cbuffer WorldMatrix : register(b0)
{
	matrix g_world;
	matrix g_worldInvTranspose;
}

cbuffer ViewMatrix : register(b1)
{
	matrix g_view;
	float3 g_eyePosW;
	float pad;

}

cbuffer ProjMatrix : register(b2)
{
	matrix g_proj;
}

cbuffer  MaterialCB : register(b3)
{
	Material g_material;
}

cbuffer LightCB : register(b4)
{
	DirectionLight g_directionLight;
}

cbuffer FogCB : register(b5)
{
	float4 g_fogColor;
	int g_fogEnabled;
	float g_fogStart;
	float g_fogRange;
	float pad222;
}
