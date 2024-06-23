cbuffer cbPerObject : register(b0)
{
    float4x4 gWorldViewProj;
    float3 cameraPosition;
};
Texture2D gTexture1 : register(t0);
SamplerState gSampler1 : register(s0);
struct VertexIn
{
    float3 PosL : POSITION;
};

struct VertexOut
{
    float4 PosL : SV_POSITION;
    float2 UV : TEXCOORD;
};

VertexOut VS_Main(VertexIn vin)
{
    VertexOut vout;
    vout.PosL = float4(vin.PosL, 1.0f);
    return vout;
}

void DrawRect(inout TriangleStream<VertexOut> outputStream, float4 position)
{      
    position.xy = position.xy * 2; 
    float3 downCam = float3(0, 1, 0);  
    float3 look = cameraPosition - position.xyz;
    look = normalize(look);
    float3 right = normalize(cross(look, downCam));
    float3 up = normalize(cross(look, right));
    
    float size = 0.5;
    float4 vertex1_pos = float4(-size, -size, 0.0f, 0.0f);
    float4 vertex2_pos = float4(-size, size, 0.0f, 0.0f);
    float4 vertex3_pos = float4(size, -size, 0.0f, 0.0f);
    float4 vertex4_pos = float4(size, size, 0.0f, 0.0f);

    vertex1_pos = float4(position.xyz - size * right, 0.0f);
    vertex2_pos = float4(position.xyz + size * right, 0.0f);
    vertex3_pos = float4(position.xyz - size * right + 2 * size * up, 0.0f);
    vertex4_pos = float4(position.xyz + size * right + 2 * size * up, 0.0f);

    float2 vertex1_uv = float2(0.0f, 0.0f);
    float2 vertex2_uv = float2(1.0f, 0.0f);
    float2 vertex3_uv = float2(0.0f, 1.0f);
    float2 vertex4_uv = float2(1.0f, 1.0f);
  
    VertexOut vertex1;
    vertex1.PosL = position + vertex1_pos;
    vertex1.PosL = mul(vertex1.PosL, gWorldViewProj);
    vertex1.UV = vertex1_uv;

    VertexOut vertex2;
    vertex2.PosL = position + vertex2_pos;
    vertex2.PosL = mul(vertex2.PosL, gWorldViewProj);
    vertex2.UV = vertex2_uv;
    
    VertexOut vertex3;
    vertex3.PosL = position + vertex3_pos;
    vertex3.PosL = mul(vertex3.PosL, gWorldViewProj);
    vertex3.UV = vertex3_uv;
    
    VertexOut vertex4;
    vertex4.PosL = position + vertex4_pos;
    vertex4.PosL = mul(vertex4.PosL, gWorldViewProj);
    vertex4.UV = vertex4_uv;
    
    outputStream.Append(vertex1);
    outputStream.Append(vertex2);
    outputStream.Append(vertex3);
    outputStream.RestartStrip();
    outputStream.Append(vertex2);
    outputStream.Append(vertex4);
    outputStream.Append(vertex3);
    outputStream.RestartStrip();

}


//Zadanie 2.1
[maxvertexcount(18)]
void GS_Main(triangle VertexOut inputData[3], inout TriangleStream<VertexOut> outputStream)
{
    DrawRect(outputStream, inputData[0].PosL);
    DrawRect(outputStream, inputData[1].PosL);
    DrawRect(outputStream, inputData[2].PosL);

}


float4 PS_Main(VertexOut pin) : SV_Target
{
    float4 color = gTexture1.Sample(gSampler1, pin.UV);
    if (color.r == 0 && color.g == 0 && color.b == 0)
    {
        discard;
    }
    
    return color;
}



