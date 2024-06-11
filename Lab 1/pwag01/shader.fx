struct VertexIn
{
	float3 Pos  : POSITION;
};

struct VertexOut
{
	float4 Pos  : SV_POSITION;
};

VertexOut VS_Main(VertexIn vin)
{
	//Zadanie 2.1.2 - Vertex Shader
	//your code here
}

float4 PS_Main(VertexOut pin) : SV_Target
{
	//Zadanie 2.1.2 - Pixel shader
	//your code here
}