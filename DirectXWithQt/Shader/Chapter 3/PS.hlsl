#include "Common.hlsli"


Texture2D g_Tex : register(t0);
Texture2D g_Tex2 : register(t2);
SamplerState g_SamplerState : register(s0);
float4 PS(VertexOut pIn) : SV_Target
{ 
	float4 color;

	[unroll]
	if (enableDM)
	{
		float2 texcoord = mul(float4(pIn.texcoord, 0, 1.0f), rotMatrix).xy;
		color = g_Tex.Sample(g_SamplerState, texcoord);
		if (enableMultiMap)
		{
			float4 color2 = g_Tex2.Sample(g_SamplerState, pIn.texcoord);
			color = color * color2;
		}
	}
	else
	{
		color = g_Tex.Sample(g_SamplerState, pIn.texcoord);
	}
	

	clip(color.a - 0.1f);


	pIn.normalW = normalize(pIn.normalW);

	float3 toEyeW = normalize(g_eyePosW - pIn.posW);

	float4 ambient, diffuse, specular;
	ambient = diffuse = specular = float4(0.0f, 0.0f, 0.0f, 0.0f);

	ComputeDirectionLight(g_material, g_directionLight, pIn.normalW, toEyeW,
		ambient,
		diffuse,
		specular);


	

	//color = color * (ambient + diffuse)+ specular;
	color.a = g_material.diffuse.a;

	return color;

}

