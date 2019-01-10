#pragma once
#include "stdafx.h"

struct TransformData
{
	D3DXMATRIX World;
};

struct CameraData
{
	D3DXMATRIX View;
	D3DXMATRIX Projection;
};

struct SpriteData
{
	D3DXVECTOR2 TextureSize;
	D3DXVECTOR2 SpriteOffset;
	D3DXVECTOR2 SpriteSize;
	float Padding[2];
};

struct ColorData
{
	D3DXCOLOR color;
};