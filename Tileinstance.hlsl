cbuffer CameraBuffer : register(b0)
{
    matrix View;
    matrix Projection;
};

//cbuffer TransformBuffer : register(b1)
//{
//    matrix World;
//};

//cbuffer SpriteBuffer : register(b2)
//{
//    float2 TextureSize;
//    float2 SpriteOffset;
//    float2 SpriteSize;
//};

//cbuffer ColorBuffer : register(b0)
//{
//    float4 Color;
//};

struct VertexInput
{
    float4 Position : POSITION0;
    float2 Uv : TEXCOORD0;

    row_major matrix World : InstanceWorld;//행우선 명시해주면 넣어주기전에 굳이 전치안해도된다.
    float2 TextureSize : InstanceTextureSize;
    float2 SpriteOffset : InstanceSpriteOffset;
    float2 SpriteSize : InstaceSpriteSize;
    float4 Color : InstanceColor;
    uint InstaceID : SV_InstanceID;//DEFAULT값 해당인스턴스가 몇번째 들어온건지 정보를 가지고있어서 몇번쨰 인스턴스데이터를 고를수있다.

};

struct PixelInput
{
    float4 Position : SV_POSITION0;
    float2 Uv : TEXCOORD0;
    float4 Color : COLOR0;
};

PixelInput VS(VertexInput input)
{
    PixelInput output;
    output.Position = mul(input.Position, input.World);
    output.Position = mul(output.Position, View);
    output.Position = mul(output.Position, Projection);

    output.Uv = input.Uv;
    output.Uv *= input.SpriteSize / input.TextureSize;
    output.Uv += input.SpriteOffset / input.TextureSize;
    output.Color = input.Color;

    return output;
}

Texture2D DiffuseMap : register(t0);
SamplerState DiffuseSamp : register(s0);

float4 PS(PixelInput input) : SV_TARGET
{
    //float4 color =  DiffuseMap.Sample(DiffuseSamp, input.Uv);
    //clip(color.a - 0.9f);
    //return color;

    return DiffuseMap.Sample(DiffuseSamp, input.Uv); //+ input.Color
}
