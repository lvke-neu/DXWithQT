struct Material
{
	float4 ambient;
	float4 diffuse;
	float4 specular;
	float4 reflect;
};

struct DirectionLight
{
	float4 ambient;
	float4 diffuse;
	float4 specular;
	float3 direction;
	float pad;
};


void ComputeDirectionLight(Material material, DirectionLight directionLight, float3 normalW, float3 toEyeW,
	out float4 ambient,
	out float4 diffuse,
	out float4 specular)
{
	ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
	diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
	specular = float4(0.0f, 0.0f, 0.0f, 0.0f);

	float3 lightDir = normalize(-directionLight.direction);

	//环境光
	ambient = material.ambient * directionLight.ambient;

	float cos_angle = dot(lightDir, normalW);

	[flatten]
	if (cos_angle > 0.0f)
	{
		//漫反射
		diffuse = material.diffuse * directionLight.diffuse * cos_angle;

		//高光
		float3 v = reflect(-lightDir, normalW);
		float specFactor = pow(max(dot(v, toEyeW), 0.0f), material.specular.w);
		specular = material.specular * directionLight.specular * specFactor;
	}
}



float3 NormalSampleToWorldSpace(float3 normalMapSample,
	float3 unitNormalW,
	float4 tangentW)
{
	// 将读取到法向量中的每个分量从[0, 1]还原到[-1, 1]
	float3 normalT = 2.0f * normalMapSample - 1.0f;

	// 构建位于世界坐标系的切线空间
	float3 N = unitNormalW;
	float3 T = normalize(tangentW.xyz - dot(tangentW.xyz, N) * N); // 施密特正交化
	float3 B = cross(N, T);

	float3x3 TBN = float3x3(T, B, N);

	// 将凹凸法向量从切线空间变换到世界坐标系
	float3 bumpedNormalW = mul(normalT, TBN);

	return bumpedNormalW;
}