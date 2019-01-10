#include "stdafx.h"
#include "Grid.h"
#include "../Component/LineRender.h"

Grid::Grid(Context * context)
	: context(context)
	, width(0)
	, height(0)
	, spacing(0)
{
	lineRender = new LineRender(context);
}

Grid::~Grid()
{
	SAFE_DELETE(lineRender);
}

void Grid::Create(const int & w, const int & h, const int & spacing, const D3DXCOLOR & color)
{
	width = (w % spacing) == 0 ? w : w - (w % spacing);
	height = (h % spacing) == 0 ? h : h - (h % spacing);

	//Vertical
	for (int i = 0; i <= width; i += spacing)
		lineRender->AddLine
		(
			D3DXVECTOR3(static_cast<float>(i), static_cast<float>(0), 0.0f),
			D3DXVECTOR3(static_cast<float>(i), static_cast<float>(height), 0.0f),
			color
		);

	//Horizontal
	for (int i = 0; i <= height; i += spacing)
		lineRender->AddLine
		(
			D3DXVECTOR3(static_cast<float>(0), static_cast<float>(i), 0.0f),
			D3DXVECTOR3(static_cast<float>(width), static_cast<float>(i), 0.0f),
			color
		);
}

void Grid::Update()
{
	lineRender->Update();
}

void Grid::Render()
{
	lineRender->Render();
}
