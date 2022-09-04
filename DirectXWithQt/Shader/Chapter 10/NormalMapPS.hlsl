#include "Common.hlsli"


Texture2D g_Tex : register(t0);
Texture2D g_normalMap : register(t1);
SamplerState g_SamplerState : register(s0);
float4 PS(VertexOut2 pIn) : SV_Target
{
	float4 color = g_Tex.Sample(g_SamplerState, pIn.texcoord);
	clip(color.a - 0.05f);


	pIn.normalW = normalize(pIn.normalW);

	float3 toEyeW = normalize(g_eyePosW - pIn.posW);
	float distToEye = distance(g_eyePosW, pIn.posW);

	float3 normalMapSample = g_normalMap.Sample(g_SamplerState, pIn.texcoord).rgb;
	float3 bumpedNormalW = NormalSampleToWorldSpace(normalMapSample, pIn.normalW, pIn.tangentW);


	float4 ambient, diffuse, specular;
	ambient = diffuse = specular = float4(0.0f, 0.0f, 0.0f, 0.0f);

	ComputeDirectionLight(g_material, g_directionLight, bumpedNormalW, toEyeW,
		ambient,
		diffuse,
		specular);

	color = color * (ambient + diffuse)+ specular;

	color.a = 1.0f;
	return color;

}

