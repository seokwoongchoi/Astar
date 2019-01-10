#pragma once

struct Vertex
{
	Vertex() : Position(0, 0, 0) {}
	Vertex(const D3DXVECTOR3& position)
		: Position(position)
	{}

	D3DXVECTOR3 Position;

	static D3D11_INPUT_ELEMENT_DESC Desc[];
	static const uint Count = 1;
};

struct VertexColor
{
	VertexColor() : Position(0, 0, 0), Color(0, 0, 0, 1) {}
	VertexColor(const D3DXVECTOR3& position, const D3DXCOLOR& color)
		: Position(position)
		, Color(color)
	{}
	VertexColor
	(
		const float& x,
		const float& y,
		const float& z,
		const D3DXCOLOR& color)
		: Position(x, y, z)
		, Color(color)
	{}

	D3DXVECTOR3 Position;
	D3DXCOLOR Color;

	static D3D11_INPUT_ELEMENT_DESC Desc[];
	static const uint Count = 2;
};

struct VertexTexture
{
	VertexTexture() : Position(0, 0, 0), Uv(0, 0) {}
	VertexTexture(const D3DXVECTOR3& position, const D3DXVECTOR2& uv)
		: Position(position)
		, Uv(uv)
	{}
	D3DXVECTOR3 Position;
	D3DXVECTOR2 Uv;

	static D3D11_INPUT_ELEMENT_DESC Desc[];
	static const uint Count = 2;
};

struct VertexTextureColor
{
	VertexTextureColor() 
		: Position(0, 0, 0)
		, Uv(0, 0) 
		, Color(0, 0, 0, 1)
	{}

	VertexTextureColor
	(
		const D3DXVECTOR3& position, 
		const D3DXVECTOR2& uv,
		const D3DXCOLOR& color
	)
		: Position(position)
		, Uv(uv)
		, Color(color)
	{}

	D3DXVECTOR3 Position;
	D3DXVECTOR2 Uv;
	D3DXCOLOR Color;

	static D3D11_INPUT_ELEMENT_DESC Desc[];
	static const uint Count = 3;
};
