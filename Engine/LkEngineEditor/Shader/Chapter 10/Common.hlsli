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


struct VertexIn2
{
	float3 posL : POSITION;
	float3 normalL : NORMAL;
	float4 tangentL : TANGENT;
	float2 texcoord : TEXCOORD;
};

struct VertexOut2
{
	float4 posH : SV_POSITION;
	float3 posW : POSITION;
	float3 normalW: NORMAL;
	float4 tangentW : TANGENT;
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

