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
    VertexOut vout;
    vout.Pos = float4(vin.Pos, 1.0f);
    return vout;
}

float4 PS_Main(VertexOut pin) : SV_Target
{
    return float4(1, 0, 0, 1);
}