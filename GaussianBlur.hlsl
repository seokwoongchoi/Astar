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

static const float GausWeight[13] =
{
    0.0561f, 0.1353f, 0.2780f, 0.4868f, 0.7261f, 0.9231f,
	1.0f,
	0.9231f, 0.7261f, 0.4868f, 0.2780f, 0.1353f, 0.0561f,
};
static const float Total = 6.2108f;

float4 PS(PixelInput input) : SV_TARGET
{
    //Gaussian Blur X
    float distance = 0.001f;
    float4 diffuse = 0;
    for (int i = -6; i < 7; i++)
    {
        float2 uv = input.Uv + float2(distance * i, 0);
        diffuse += GausWeight[6 + i] * DiffuseMap.Sample(DiffuseSamp, uv);
    }
    diffuse /= Total;

    return float4(diffuse.rgb, 1.0f);

}
