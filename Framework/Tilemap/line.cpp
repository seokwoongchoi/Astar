#include "stdafx.h"
#include "Line.h"

Line::Line()
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

Line::~Line()
{
}

void Line::Initialize(Context * context)
{
	this->context = context;
	resourceMgr = context->GetSubsystem<ResourceManager>();
}

const D3DXVECTOR3 Line::GetPosition() const
{
	return D3DXVECTOR3(position.x, position.y, 1.0f);
}

const D3DXVECTOR3 Line::GetSize() const
{
	return D3DXVECTOR3(size.x, size.y, 1.0f);
}

void Line::SetTexture(const string & filePath)
{
	texture = resourceMgr->LoadFromFile<Texture2D>(filePath);
}

void Line::SetSpriteData(const D3DXVECTOR2 & offset, const D3DXVECTOR2 & size)
{
	spriteOffset = offset;
	spriteSize = size;
}

void Line::SetSpriteData(const float & x, const float & y, const float & size)
{
	SetSpriteData(D3DXVECTOR2(x, y), D3DXVECTOR2(size, size));
}

void Line::SetTileLocation(const D3DXVECTOR2 & position, const D3DXVECTOR2 & size)
{
	this->position = position + size * 0.5f;
	this->size = size;

	SetPosition(position.x, position.y);
}

void Line::SetTileLocation(const float & x, const float & y, const float & size)
{
	SetTileLocation(D3DXVECTOR2(x, y), D3DXVECTOR2(size, size));
}
