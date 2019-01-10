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
    float3 mask[9] =
    {
        //X, Y, Weight
        float3(-1, -1, -1), float3(0, -1, -1), float3(1, -1, -1),
        float3(-1, +0, -1), float3(0, +0, +8), float3(1, +0, -1),
        float3(-1, +1, -1), float3(0, +1, -1), float3(1, +1, -1),
    };

    float4 color = 0;
    for (int i = 0; i < 9; i++)
    {
        float x = mask[i].x / 1024; //이미지 싸이즈
        float y = mask[i].y / 720;
        float weight = mask[i].z;

        float2 uv = input.Uv + float2(x, y);
        color += DiffuseMap.Sample(DiffuseSamp, uv) * weight;
    }

    float4 mono = float4(0.299f, 0.587f, 0.114f, 1.0f);
    float c = dot(color, mono);

    c *= -15; //양각인지 음각인지

    return float4(c, 0, 0, 1);

}
