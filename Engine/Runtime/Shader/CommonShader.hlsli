cbuffer WorlMatrixCB : register(b0)
{
	matrix g_worldMatrix;
};

cbuffer ViewMatrixCB : register(b1)
{
	matrix g_viewMatrix;
};

cbuffer ProjMatrixCB : register(b2)
{
	matrix g_projMatrix;
};

struct VsIn
{
	float3 pos : POSITION;
	float3 normal : NORMAL;
	float2 uv  : TEXCOORD;
};

struct VsOut
{
	float4 pos : SV_POSITION;
	float2 uv  : TEXCOORD;
};

