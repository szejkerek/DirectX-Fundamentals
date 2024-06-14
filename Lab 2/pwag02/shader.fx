cbuffer cbCamera : register(b0)
{
    float4x4 gViewMatrix;
    float4x4 gProjMatrix;
};
cbuffer cbWorld : register(b1)
{
    float4x4 gWorldMatrix;
};

struct VertexIn
{
    float3 PosL : POSITION;
    float4 color : COLOR;
};

struct VertexOut
{
    float4 PosH : SV_POSITION;
    float4 color : COLOR;
};

VertexOut VS_Main(VertexIn vin)
{
    VertexOut vout;

    float4x4 worldViewProjection = float4x4(
		1.00, 0.00, 0.00, 0.00,
		0.00, 1.00, 0.00, 0.00,
		0.00, 0.00, 1.00, 0.00,
		0.00, 0.00, 0.00, 1.00
	);

    vout.PosH = mul(float4(vin.PosL, 1.0f), gWorldMatrix);
    vout.PosH = mul(vout.PosH, gViewMatrix);
    vout.PosH = mul(vout.PosH, gProjMatrix);
    vout.color = vin.color;
    return vout;
}

float4 PS_Main(VertexOut pin) : SV_Target
{
    return float4(pin.color);
}