#include "stdafx.h"
#include "GenericGeometry.h"

void GenericGeometry::CreateQuadToVertexTexture(Mesh* mesh)
{
	mesh->AddVertex(VertexTexture(D3DXVECTOR3(-0.5f, -0.5f, 0), D3DXVECTOR2(0, 1)));
	mesh->AddVertex(VertexTexture(D3DXVECTOR3(-0.5f, +0.5f, 0), D3DXVECTOR2(0, 0)));
	mesh->AddVertex(VertexTexture(D3DXVECTOR3(+0.5f, -0.5f, 0), D3DXVECTOR2(1, 1)));
	mesh->AddVertex(VertexTexture(D3DXVECTOR3(+0.5f, +0.5f, 0), D3DXVECTOR2(1, 0)));

	mesh->AddIndex(0); mesh->AddIndex(1); mesh->AddIndex(2);
	mesh->AddIndex(2); mesh->AddIndex(1); mesh->AddIndex(3);

	mesh->CreateBuffers();
}

void GenericGeometry::CreateScreenQuad(Mesh* mesh)
{
	float w = Settings::Get()->GetWidth() * 0.5f;
	float h = Settings::Get()->GetHeight() * 0.5f;

	mesh->AddVertex(VertexTexture(D3DXVECTOR3(-w, -h, 0), D3DXVECTOR2(0, 1)));
	mesh->AddVertex(VertexTexture(D3DXVECTOR3(-w, +h, 0), D3DXVECTOR2(0, 0)));
	mesh->AddVertex(VertexTexture(D3DXVECTOR3(+w, -h, 0), D3DXVECTOR2(1, 1)));
	mesh->AddVertex(VertexTexture(D3DXVECTOR3(+w, +h, 0), D3DXVECTOR2(1, 0)));

	mesh->AddIndex(0); mesh->AddIndex(1); mesh->AddIndex(2);
	mesh->AddIndex(2); mesh->AddIndex(1); mesh->AddIndex(3);

	mesh->CreateBuffers();
}
