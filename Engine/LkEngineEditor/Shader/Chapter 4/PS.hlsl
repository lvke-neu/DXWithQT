#include "Common.hlsli"


Texture2D g_Tex : register(t0);
SamplerState g_SamplerState : register(s0);
float4 PS(VertexOut pIn) : SV_Target
{

	pIn.normalW = normalize(pIn.normalW);

	float3 toEyeW = normalize(g_eyePosW - pIn.posW);

	float4 ambient, diffuse, specular;
	ambient = diffuse = specular = float4(0.0f, 0.0f, 0.0f, 0.0f);

	ComputeDirectionLight(g_material, g_directionLight, pIn.normalW, toEyeW,
		ambient,
		diffuse,
		specular);


	float4 color = g_Tex.Sample(g_SamplerState, pIn.texcoord);

	//color = color * (ambient + diffuse)+ specular;
	//color.a = 1.0f;
	color.a = g_material.diffuse.a;
	return color;

}

