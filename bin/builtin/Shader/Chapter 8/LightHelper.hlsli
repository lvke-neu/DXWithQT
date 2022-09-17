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