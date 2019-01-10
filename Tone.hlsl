cbuffer CameraBuffer : register(b0)
{
    matrix View;
    matrix Projection;
};

struct VertexInput
{
    float4 Position : POSITION0;
    float2 Uv : TEXCOORD0;
};

struct PixelInput
{
    float4 Position : SV_POSITION0;
    float2 Uv : TEXCOORD0;
};

PixelInput VS(VertexInput input)
{
    PixelInput output;
    output.Position = mul(input.Position, View);
    output.Position = mul(output.Position, Projection);

    output.Uv = input.Uv;

    return output;
}

Texture2D DiffuseMap : register(t0);
SamplerState DiffuseSamp : register(s0);

float4 PS(PixelInput input) : SV_TARGET
{
    //1
    //float4 color = DiffuseMap.Sample(DiffuseSamp, input.Uv);
    //float c = (color.r + color.g + color.b) / 3.0f;
    //
    //return float4(c, c, c, 1.0f);

    //2
    //float3 factor = float3(0.298f, 0.587f, 0.114f);
    //float4 color = DiffuseMap.Sample(DiffuseSamp, input.Uv);

    //float c = dot(color.rgb, factor);

    //return float4(c, c, c, 1.0f);

    //Negative
    float4 color = DiffuseMap.Sample(DiffuseSamp, input.Uv);
    float r = 1 - color.r;
    float g = 1 - color.g;
    float b = 1 - color.b;
    
    return float4(r, g, b, 1);
}
