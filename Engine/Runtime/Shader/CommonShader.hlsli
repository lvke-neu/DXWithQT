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

cbuffer MVP : register(b0)
{
	matrix g_mvp;
};