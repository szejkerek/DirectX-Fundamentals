# DirectX Fundamentals

A series of five progressive DirectX 12 labs covering the full GPU rendering pipeline — from a bare triangle to tessellation with heightmap displacement.

## Code Highlights

### Camera-Aligned Billboard Generation in the Geometry Shader

**File:** `Lab 4/pwag04/shader.fx`, lines 26–91

```hlsl
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

[maxvertexcount(18)]
void GS_Main(triangle VertexOut inputData[3], inout TriangleStream<VertexOut> outputStream)
{
    DrawRect(outputStream, inputData[0].PosL);
    DrawRect(outputStream, inputData[1].PosL);
    DrawRect(outputStream, inputData[2].PosL);
}
```

The geometry shader takes a single input triangle and expands each of its three vertices into a camera-facing quad (two triangles each), emitting up to 18 vertices total. For each billboard, it computes a view-aligned orthonormal basis on the GPU: the `look` vector points from the vertex toward the camera, then `cross(look, world_up)` gives `right`, and `cross(look, right)` gives `up`. The four quad corners are placed symmetrically around the origin vertex using these basis vectors, then transformed to clip space. The pixel shader discards fragments where all RGB channels are black, providing cheap alpha cutout transparency without requiring blend state changes.

---

### Heightmap Displacement via the Tessellation Pipeline (Domain Shader)

**File:** `Lab 5/pwag05/shader.fx`, lines 75–102

```hlsl
[domain("quad")]
DomainOut DS_Main(PatchTess patchTess, float2 uv : SV_DomainLocation, const OutputPatch<HullOut, 4> quad)
{
    DomainOut dout;

    //Vertex position
    float3 v1 = lerp(quad[0].PosL, quad[1].PosL, uv.x);
    float3 v2 = lerp(quad[3].PosL, quad[2].PosL, uv.x);
    float3 p = lerp(v1, v2, uv.y);
    
    float2 uvV1 = lerp(quad[0].uv, quad[1].uv, uv.x);
    float2 uvV2 = lerp(quad[3].uv, quad[2].uv, uv.x);
    float2 uvP = lerp(uvV1, uvV2, uv.y);
    float4 color = gTexture1.SampleLevel(gSampler1, uvP, 0);
    p.y = color.y;
    
    dout.PosH = mul(float4(p, 1.0f), gWorldViewProj);
    dout.uv = uvP;
    return dout;
}
```

After the hull shader emits control points and sets tessellation factors, the fixed-function tessellator subdivides the quad patch and invokes the domain shader once per generated vertex, passing its normalized (u,v) parameter-space coordinates. The domain shader reconstructs world-space position with two bilinear `lerp` chains across the patch corners, performs the identical interpolation for texture coordinates, then samples the heightmap using `SampleLevel` at explicit LOD 0 — avoiding automatic mip selection that would blur the displacement at grazing angles. The green channel of the sampled texel directly replaces the vertex's Y coordinate, converting a flat patch into a terrain surface entirely on the GPU.
