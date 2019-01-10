cbuffer CameraBuffer : register(b0)
{
    matrix View;
    matrix Projection;
};

struct VertexInput
{
    float4 Position : POSITION0;
    float4 Color : COLOR0;
};

struct PixelInput
{
    float4 Position : SV_POSITION0;
    float4 Color : COLOR0;
};

PixelInput VS(VertexInput input)
{
    PixelInput output;
    output.Position = mul(input.Position, View);
    output.Position = mul(output.Position, Projection);
    output.Color = input.Color;

    return output;
}

float4 PS(PixelInput input) : SV_TARGET
{
    return input.Color;
}
