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
    float4 diffuse = 0;
    float2 distance = float2(0.001f, 0.001f);
    diffuse += DiffuseMap.Sample(DiffuseSamp, float2(input.Uv.x - distance.x, input.Uv.y));
    diffuse += DiffuseMap.Sample(DiffuseSamp, float2(input.Uv.x + distance.y, input.Uv.y));
    diffuse += DiffuseMap.Sample(DiffuseSamp, float2(input.Uv.x, input.Uv.y - distance.y));
    diffuse += DiffuseMap.Sample(DiffuseSamp, float2(input.Uv.x, input.Uv.y + distance.y));

    diffuse /= 4;
    return float4(diffuse.rgb, 1.0f);
}
