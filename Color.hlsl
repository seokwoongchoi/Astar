cbuffer WorldViewProjection : register(b0)
{
    matrix World;
    matrix View;
    matrix Projection;
};

cbuffer ColorBuffer : register(b0)
{
    float4 Color;
};

struct VertexInput
{
    float4 Position : POSITION0;
};

struct PixelInput
{
    float4 Position : SV_POSITION0;
};

PixelInput VS(VertexInput input)
{
    PixelInput output;
    output.Position = mul(input.Position, World);
    output.Position = mul(output.Position, View);
    output.Position = mul(output.Position, Projection);

    return output;
}

float4 PS(PixelInput input) : SV_TARGET
{
    return Color;
}
