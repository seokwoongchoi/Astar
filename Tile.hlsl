cbuffer CameraBuffer : register(b0)
{
    matrix View;
    matrix Projection;
};

cbuffer TransformBuffer : register(b1)
{
    matrix World;
};

cbuffer SpriteBuffer : register(b2)
{
    float2 TextureSize;
    float2 SpriteOffset;
    float2 SpriteSize;
};

cbuffer ColorBuffer : register(b0)
{
    float4 Color;
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
    output.Position = mul(input.Position, World);
    output.Position = mul(output.Position, View);
    output.Position = mul(output.Position, Projection);

    output.Uv = input.Uv;
    output.Uv *= SpriteSize / TextureSize;
    output.Uv += SpriteOffset / TextureSize;

    return output;
}

Texture2D DiffuseMap : register(t0);
SamplerState DiffuseSamp : register(s0);

float4 PS(PixelInput input) : SV_TARGET
{
    //float4 color =  DiffuseMap.Sample(DiffuseSamp, input.Uv);
    //clip(color.a - 0.9f);
    //return color;

    return DiffuseMap.Sample(DiffuseSamp, input.Uv)+Color;
}
