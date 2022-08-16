struct VertexIn
{
	float3 posL : POSITION;
	float3 normalL : NORMAL;
	float2 texcoord : TEXCOORD;
};

struct VertexOut
{
	float4 posH : SV_POSITION;
	float3 posW : POSITION0;
	float3 normalW: NORMAL;
	float2 texcoord: TEXCOORD;
	float3 posL : POSITION1;
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


