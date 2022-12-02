struct VsOut
{
	float3 color : COLOR;
	float4 pos : SV_Position;
};

VsOut  main(float2 pos: POSITION, float3 color : COLOR)
{
	VsOut vo;
	vo.pos = float4(pos.x, pos.y, 0.0f, 1.0f);
	vo.color = color;
	return vo;
}