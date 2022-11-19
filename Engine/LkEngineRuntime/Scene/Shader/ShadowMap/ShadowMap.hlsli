struct VertexIn
{
	float3 PosL : POSITION;
	float3 NormalL : NORMAL;
	float2 Tex : TEXCOORD;
};

struct VertexOut
{
	float4 PosH : SV_POSITION;
	float2 Tex : TEXCOORD;
};

cbuffer ViewMatrix : register(b10)
{
	matrix g_view;
}

cbuffer ProjMatrix : register(b11)
{
	matrix g_orthographiProj;
}

cbuffer WorldMatrix : register(b3)
{
	matrix g_world;

}
