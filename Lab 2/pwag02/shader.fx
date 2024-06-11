//Zadanie 2.1.3 program cieniujacy wierzcholki i piksele
struct VertexIn
{
	float3 PosL  : POSITION;
	//dodaj kolor
};

struct VertexOut
{
	float4 PosH  : SV_POSITION;
	//dodaj kolor
};

VertexOut VS_Main(VertexIn vin)
{
	VertexOut vout;

	// Zadanie 2.2.5 - program cieniujacy wierzcholki
	//Zamiast umieszczonej ponizej statycznej macierzy
	//wykorzystaj macierze zapisane przez ciebie w buforze stalych
	float4x4 worldViewProjection = float4x4(
		2.41, 0.00, 0.00, 0.00,
		0.00, 2.41, 0.00, 0.00,
		0.00, 0.00, 1.00, 1.00,
		0.00, 0.00, 4.00, 5.00
	);

	// Transform to homogeneous clip space.
	vout.PosH = mul(float4(vin.PosL, 1.0f), worldViewProjection);

	return vout;
}

float4 PS_Main(VertexOut pin) : SV_Target
{
	return float4(1.0f, 0.0f, 0.0f, 1.0f); //Zadanie 2.1.3 wyswietl kolor
}