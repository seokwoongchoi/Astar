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
    return DiffuseMap.Sample(DiffuseSamp, input.Uv * 2);
}
