cbuffer cbPerObject : register(b0)
{
	float4x4 gWorldViewProj;
};

struct VertexIn
{
	float3 PosL  : POSITION;
};

struct VertexOut
{
	float4 PosL  : SV_POSITION;
};


VertexOut VS_Main(VertexIn vin)
{
	VertexOut vout;
	vout.PosL = float4(vin.PosL, 1.0f);
	return vout;
}


//Zadanie 2.1
[maxvertexcount(2)]
void GS_Main(line VertexOut inputData[2], inout LineStream<VertexOut> outputStream) //Zadanie 2.2 - zmien geometrie na punkt
{
	//Program cieniujacy geometrie
	outputStream.Append(inputData[0]);
	outputStream.Append(inputData[1]);
}

Texture2D    gTexture1 : register(t0);
SamplerState gSampler1  : register(s0);
float4 PS_Main(VertexOut pin) : SV_Target
{
	return float4(1.0f, 0.0f, 0.0f, 1.0f); //Zadanie 2.3 Wspolrzednie uv
}

/* Zadanie 2.2 - funkcja generujaca kwadrat z punktu
void DrawRect(inout TriangleStream<VertexOut> outputStream, float4 position)
{
	float size = 0.5;
	float4 vertex1_pos = float4(-size, -size, 0.0f, 0.0f);
	float4 vertex2_pos = float4(-size, size, 0.0f, 0.0f);
	float4 vertex3_pos = float4(size, -size, 0.0f, 0.0f);
	float4 vertex4_pos = float4(size, size, 0.0f, 0.0f);

	VertexOut vertex1;
	vertex1.PosL = position + vertex1_pos;

	VertexOut vertex2;
	vertex2.PosL = position + vertex2_pos;

	VertexOut vertex3;
	vertex3.PosL = position + vertex3_pos;

	VertexOut vertex4;
	vertex4.PosL = position + vertex4_pos;

	outputStream.Append(vertex1);
	outputStream.Append(vertex2);
	outputStream.Append(vertex3);
	outputStream.RestartStrip();
	outputStream.Append(vertex2);
	outputStream.Append(vertex4);
	outputStream.Append(vertex3);
	outputStream.RestartStrip();
}
*/