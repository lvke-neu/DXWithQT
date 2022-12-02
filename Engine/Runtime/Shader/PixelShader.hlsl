cbuffer ColorCB : register(b0)
{
	float4 g_color;
}

float4 main(float3 color : COLOR) : SV_Target
{
	return g_color;
}