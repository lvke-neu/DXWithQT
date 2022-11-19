
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

cbuffer ViewMatrix : register(b0)
{
	matrix g_view;
	float3 g_eyePosW;
	float pad;

}

cbuffer ProjMatrix : register(b1)
{
	matrix g_proj;
	matrix g_invProj;
	float4 g_viewportSize;
}

cbuffer DirectionLightCB : register(b2)
{
	DirectionLight g_dirLight;
}

cbuffer ShadowTransformCB : register(b12)
{
	matrix g_ShadowTransform;
}

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

static const float SMAP_SIZE = 2048.0f;
static const float SMAP_DX = 1.0f / SMAP_SIZE;

float CalcShadowFactor(SamplerComparisonState samShadow,
	Texture2D shadowMap,
	float4 shadowPosH)
{
	// 透视除法
	shadowPosH.xyz /= shadowPosH.w;

	// NDC空间的深度值
	float depth = shadowPosH.z;

	// 纹素在纹理坐标下的宽高
	const float dx = SMAP_DX;

	float percentLit = 0.0f;
	const float2 offsets[9] =
	{
		float2(-dx, -dx), float2(0.0f, -dx), float2(dx, -dx),
		float2(-dx, 0.0f), float2(0.0f, 0.0f), float2(dx, 0.0f),
		float2(-dx, +dx), float2(0.0f, +dx), float2(dx, +dx)
	};

	// samShadow为compareValue <= sampleValue时为1.0f(反之为0.0f), 对相邻四个纹素进行采样比较
	// 并根据采样点位置进行双线性插值
	// float result0 = depth <= s0;  // .s0      .s1          
	// float result1 = depth <= s1;
	// float result2 = depth <= s2;  //     .depth
	// float result3 = depth <= s3;  // .s2      .s3
	// float result = BilinearLerp(result0, result1, result2, result3, a, b);  // a b为算出的插值相对位置                           
	[unroll]
	for (int i = 0; i < 9; ++i)
	{
		percentLit += shadowMap.SampleCmpLevelZero(samShadow,
			shadowPosH.xy + offsets[i], depth).r;
	}

	return percentLit /= 9.0f;
}
