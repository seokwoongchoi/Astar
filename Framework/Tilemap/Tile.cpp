#include "stdafx.h"
#include "Tile.h"

Tile::Tile()
	: context(nullptr)
	, resourceMgr(nullptr)
	, texture(nullptr)
	, spriteOffset(0, 0)
	, spriteSize(1, 1)
	, position(0, 0)
	, size(1, 1)
	, color(1, 1, 1, 1)
	, bWalkable(true)
{
}

Tile::~Tile()
{
}

void Tile::Initialize(Context * context)
{
	this->context = context;
	resourceMgr = context->GetSubsystem<ResourceManager>();
}

const D3DXVECTOR3 Tile::GetPosition() const
{
	return D3DXVECTOR3(position.x, position.y, 1.0f);
}

const D3DXVECTOR3 Tile::GetSize() const
{
	return D3DXVECTOR3(size.x, size.y, 1.0f);
}

void Tile::SetTexture(const string & filePath)
{
	texture = resourceMgr->LoadFromFile<Texture2D>(filePath);
}

void Tile::SetSpriteData(const D3DXVECTOR2 & offset, const D3DXVECTOR2 & size)
{
	spriteOffset = offset;
	spriteSize = size;
}

void Tile::SetSpriteData(const float & x, const float & y, const float & size)
{
	SetSpriteData(D3DXVECTOR2(x, y), D3DXVECTOR2(size, size));
}

void Tile::SetTileLocation(const D3DXVECTOR2 & position, const D3DXVECTOR2 & size)
{
	this->position = position + size * 0.5f;
	this->size = size;

	SetPosition(position.x, position.y);
}

void Tile::SetTileLocation(const float & x, const float & y, const float & size)
{
	SetTileLocation(D3DXVECTOR2(x, y), D3DXVECTOR2(size, size));
}
