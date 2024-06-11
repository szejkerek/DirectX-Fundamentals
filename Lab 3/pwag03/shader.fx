cbuffer cbPerObject : register(b0)
{
	float4x4 gWorldViewProj;
};

struct VertexIn
{
	float3 PosL  : POSITION;
	float2 UV : TEXCOORD;
};

struct VertexOut
{
	float4 PosH  : SV_POSITION;
};

VertexOut VS_Main(VertexIn vin)
{
	VertexOut vout;

	// Transform to homogeneous clip space.
	vout.PosH = mul(float4(vin.PosL, 1.0f), gWorldViewProj);

	return vout;
}

//Zadanie 2.1.4 
//Przepisz program cieniujacy tak aby korzystal z wczytanej przez ciebie tekstury
float4 PS_Main(uint pid: SV_PrimitiveID) : SV_Target
{
	//pseudo-random colors
	float red = (pid % 11) / 11.0f;
	float green = 1.0f - ((pid % 7) / 6.0f);
	float blue = (pid % 4) / 4.0f;
	return float4(red, green , blue, 1.0f);
}