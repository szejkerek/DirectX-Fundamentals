cbuffer cbPerObject : register(b0)
{
    float4x4 gWorldViewProj;
};
Texture2D gTexture : register(t0);
Texture2D gTexture2 : register(t1);
SamplerState gSampler : register(s0);
struct VertexIn
{
    float3 PosL : POSITION;
    float2 UV : TEXCOORD;
};

struct VertexOut
{
    float4 PosH : SV_POSITION;
    float2 UV : TEXCOORD;
};

VertexOut VS_Main(VertexIn vin)
{
    VertexOut vout;

	// Transform to homogeneous clip space.
    vout.PosH = mul(float4(vin.PosL, 1.0f), gWorldViewProj);
    vout.UV = vin.UV;
    return vout;
}

//Zadanie 2.1.4 
//Przepisz program cieniujacy tak aby korzystal z wczytanej przez ciebie tekstury
float4 PS_Main(VertexOut pin) : SV_Target
{
	//pseudo-random colors
    float4 color;
    color = gTexture.Sample(gSampler, pin.UV);
    float4 color2 = gTexture2.Sample(gSampler, pin.UV);
    color = color - color2;
    return color;
}