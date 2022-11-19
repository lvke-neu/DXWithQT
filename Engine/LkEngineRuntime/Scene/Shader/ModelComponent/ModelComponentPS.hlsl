#include "ModelComponent.hlsli"

Texture2D g_Tex : register(t0);
SamplerState g_SamplerState : register(s0);
Texture2D g_ShadowMap : register(t1);
SamplerComparisonState g_SamShadow : register(s1);

float4 PS(VertexOut pIn) : SV_Target
{
	float4 color = g_Tex.Sample(g_SamplerState, pIn.texcoord);
	clip(color.a - 0.05f);

	pIn.normalW = normalize(pIn.normalW);

	float3 toEyeW = normalize(g_eyePosW - pIn.posW);

	float shadow = 1.0f;
	shadow = CalcShadowFactor(g_SamShadow, g_ShadowMap, pIn.ShadowPosH);

	float4 ambient, diffuse, spec;
	float4 A, D, S;
	ambient = diffuse = spec = A = D = S = float4(0.0f, 0.0f, 0.0f, 0.0f);

	ComputeDirectionLight(g_material, g_dirLight, pIn.normalW, toEyeW, A, D, S);
	ambient += A;
	diffuse += shadow * D;
	spec += shadow * S;

	color = color * (ambient + diffuse) + spec;

	color.a = g_material.diffuse.a * color.a;

	return color;
}