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

cbuffer EnableShadowCB : register(b5)
{
	float g_isShadow;
	float3 pad222;
}

cbuffer ShadowMatrixCB : register(b6)
{
	matrix g_shadowMatrix;
}

