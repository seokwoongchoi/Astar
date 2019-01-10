#include "stdafx.h"
#include "LineRender.h"

LineRender::LineRender(Context * context)
	: context(context)
	, vertexCount(0)
{
	vertexBuffer = new VertexBuffer(context->GetSubsystem<Graphics>());
	shader =
		context->GetSubsystem<ResourceManager>()->LoadFromFile<Shader>("Line.hlsl");
}

LineRender::~LineRender()
{
	vertices.clear();
	vertices.shrink_to_fit();

	SAFE_DELETE(vertexBuffer);
}

void LineRender::AddLine(const D3DXVECTOR3 & start, const D3DXVECTOR3 & end, const D3DXCOLOR & color)
{
	AddVertex(VertexColor(start, color));
	AddVertex(VertexColor(end, color));
}

void LineRender::AddLine(const float & startX, const float & startY, const float & endX, const float & endY, const float & r, const float & g, const float & b, const float & a)
{
	AddLine
	(
		D3DXVECTOR3(startX, startY, 0.0f),
		D3DXVECTOR3(endX, endY, 0.0f),
		D3DXCOLOR(r, g, b, a)
	);
}

void LineRender::AddLines(const vector<VertexColor>& lines)
{
	vertices.insert(vertices.end(), lines.begin(), lines.end());
}

void LineRender::AddBoundBox(const BoundBox & box, D3DXCOLOR & color)
{
	//minx, miny - 1      maxx, miny - 3
	//minx, maxy - 4      maxx, maxy - 2

	D3DXVECTOR3 boundPoint1 = box.GetMin();
	D3DXVECTOR3 boundPoint2 = box.GetMax();
	D3DXVECTOR3 boundPoint3 = D3DXVECTOR3(boundPoint2.x, boundPoint1.y, 0.0f);
	D3DXVECTOR3 boundPoint4 = D3DXVECTOR3(boundPoint1.x, boundPoint2.y, 0.0f);

	AddLine(boundPoint1, boundPoint3, color);
	AddLine(boundPoint3, boundPoint2, color);
	AddLine(boundPoint2, boundPoint4, color);
	AddLine(boundPoint4, boundPoint1, color);
}

void LineRender::Clear()
{
	vertices.clear();
	vertices.shrink_to_fit();
}

void LineRender::Update()
{
	if (vertexCount != vertices.size())
	{
		vertexCount = vertices.size();
		CreateVertexBuffer();
		UpdateVertexBuffer();
	}
}

void LineRender::Render()
{
	shader->BindPipeline();
	vertexBuffer->BindPipeline();

	auto graphics = context->GetSubsystem<Graphics>();
	graphics->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
	graphics->GetDeviceContext()->Draw(vertexCount, 0);
}

void LineRender::AddVertex(const VertexColor & vertex)
{
	vertices.push_back(vertex);
}

void LineRender::AddVertex(const D3DXVECTOR3 & position, const D3DXCOLOR & color)
{
	AddVertex(VertexColor(position, color));
}

void LineRender::AddVertex(const float & x, const float & y, const float & z, const float & r, const float & g, const float & b, const float & a)
{
	AddVertex(D3DXVECTOR3(x, y, z), D3DXCOLOR(r, g, b, a));
}

void LineRender::CreateVertexBuffer()
{
	vertexBuffer->Clear();
	vertexBuffer->Create<VertexColor>(vertices, D3D11_USAGE_DYNAMIC);
}

void LineRender::UpdateVertexBuffer()
{
	auto data = vertexBuffer->Map();
	memcpy(data, vertices.data(), sizeof(VertexColor) * vertices.size());
	vertexBuffer->Unmap();
}
