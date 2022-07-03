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

cbuffer VsConstantBuffer : register(b0)
{
	matrix g_world;
	matrix g_view;
	matrix g_proj;
}