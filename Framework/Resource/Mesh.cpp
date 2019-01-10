#include "stdafx.h"
#include "Mesh.h"

Mesh::Mesh(Context * context)
	: IResource(context)
	, topology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
{
	vertexBuffer = new VertexBuffer(context->GetSubsystem<Graphics>());
	indexBuffer = new IndexBuffer(context->GetSubsystem<Graphics>());
}

Mesh::~Mesh()
{
	SAFE_DELETE(indexBuffer);
	SAFE_DELETE(vertexBuffer);
}

void Mesh::AddVertices(const vector<VertexTexture>& val)
{
	vertices.clear(); // 배열을 비움
	vertices.shrink_to_fit();// 배열 공간을 축소
	vertices.assign(val.begin(), val.end());//배열 재할당
}

void Mesh::AddIndices(const vector<uint>& val)
{
	indices.clear();
	indices.shrink_to_fit();
	indices.assign(val.begin(), val.end());
}

void Mesh::CreateBuffers()
{
	vertexBuffer->Clear();
	vertexBuffer->Create<VertexTexture>(vertices);

	indexBuffer->Clear();
	indexBuffer->Create(indices);
}

void Mesh::BindPipeline()
{
	auto graphics = context->GetSubsystem<Graphics>();
	graphics->GetDeviceContext()->IASetPrimitiveTopology(topology);
	vertexBuffer->BindPipeline();
	indexBuffer->BindPipeline();
}

void Mesh::SaveToFile(const string & saveFilePath)
{
}

void Mesh::LoadFromFile(const string & loadFilePath)
{
	if (loadFilePath == "Quad")
		GenericGeometry::CreateQuadToVertexTexture(this);
	else if (loadFilePath == "ScreenQuad")
		GenericGeometry::CreateScreenQuad(this);
	else
	{
		//TODO : Xml Read 처리할것
	}
}
