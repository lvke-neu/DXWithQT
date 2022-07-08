struct VertexIn
{
	float3 posL : POSITION;
	float3 normalL : NORMAL;
	float2 texcoord : TEXCOORD;
};

struct VertexOut
{
	float4 posH : SV_POSITION;
	float4 normal: NORMAL;
	float2 texcoord: TEXCOORD;

};

cbuffer WorldMatrix : register(b0)
{
	matrix g_world;
}

cbuffer ViewMatrix : register(b1)
{
	matrix g_view;
}

cbuffer ProjMatrix : register(b2)
{
	matrix g_proj;
}