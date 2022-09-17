struct VertexIn
{
	float3 pos : POSITION;

};

struct VertexOut
{
	float4 posH : SV_POSITION;

};

cbuffer PsConstantBuffer : register(b0)
{
	float4 color;
}