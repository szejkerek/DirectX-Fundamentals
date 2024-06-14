//Zadanie 2.1.3 program cieniujacy wierzcholki i piksele
cbuffer cbCamera : register(b0)
{
    float4x4 gViewMatrix;
    float4x4 gProjMatrix;
};

struct VertexIn
{
	float3 PosL  : POSITION;
    float4 color : COLOR;
	//dodaj kolor
};

struct VertexOut
{
	float4 PosH  : SV_POSITION;
    float4 color : COLOR;
};

VertexOut VS_Main(VertexIn vin)
{
	VertexOut vout;

	// Zadanie 2.2.5 - program cieniujacy wierzcholki
	float4x4 worldViewProjection = float4x4(
		1.41, 0.00, 0.00, 0.00,
		0.00, 1.41, 0.00, 0.00,
		0.00, 0.00, 1.00, 1.00,
		0.00, 0.00, 4.00, 5.00
	);

	// Transform to homogeneous clip space.
	vout.PosH = mul(float4(vin.PosL, 1.0f), worldViewProjection);
    vout.color = vin.color;
	return vout;
}

float4 PS_Main(VertexOut pin) : SV_Target
{
    return float4(pin.color);
}