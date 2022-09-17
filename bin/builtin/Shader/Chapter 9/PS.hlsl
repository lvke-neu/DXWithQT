#include "Common.hlsli"


Texture2D g_Tex : register(t0);
TextureCube g_TexCube : register(t3);
SamplerState g_SamplerState : register(s0);

float4 PS(VertexOut pIn) : SV_Target
{
	float4 color = g_Tex.Sample(g_SamplerState, pIn.texcoord);
	clip(color.a - 0.05f);


	pIn.normalW = normalize(pIn.normalW);

	float3 toEyeW = normalize(g_eyePosW - pIn.posW);


	float4 ambient, diffuse, specular;
	ambient = diffuse = specular = float4(0.0f, 0.0f, 0.0f, 0.0f);

	ComputeDirectionLight(g_material, g_directionLight, pIn.normalW, toEyeW,
		ambient,
		diffuse,
		specular);

	color = color * (ambient + diffuse)+ specular;

	if (g_ReflectionEnabled)
	{
		float3 incident = -toEyeW;
		float3 reflectionVector = reflect(incident, pIn.normalW);
		float4 reflectionColor = g_TexCube.Sample(g_SamplerState, reflectionVector);

		color += g_material.reflect * reflectionColor;
	}

	color.a = color.a * g_material.diffuse.a;
	//color.a = 1;
	return color;

}

