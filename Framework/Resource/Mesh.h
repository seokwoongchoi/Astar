#pragma once
#include "IResource.h"
//정점 데이터, 버텍스 버퍼, 인덱스버퍼를 모아서 관리하는 클래스
class Mesh : public IResource
{
public:
	Mesh(class Context* context);
	virtual ~Mesh();
	
	VertexBuffer* GetVertexBuffer()const { return vertexBuffer; }

	//Gatter 함수
	const vector<VertexTexture>& GetVertices() const { return vertices; }
	const vector<uint>& GetIndices() const { return indices; }
	VertexTexture const* GetVerticesPtr() const { return vertices.data(); }
	uint const* GetIndicesPtr() const { return indices.data(); }
	const uint GetVertexCount() const { return vertices.size(); }
	const uint GetIndexCount() const { return indices.size(); }


	void SetTopology(const D3D11_PRIMITIVE_TOPOLOGY& topology) { this->topology = topology; }
	
	//정점 데이터 하나씩 추가하는 함수
	void AddVertex(const VertexTexture& vertex) { vertices.push_back(vertex); }
	//인덱스 데이터 하나씩 추가하는 함수
	void AddIndex(const uint& index) { indices.push_back(index); }
	
	//얘들은 통으로 넘기는 놈
	void AddVertices(const vector<VertexTexture>& val);
	void AddIndices(const vector<uint>& val);

	//내가 추가할 정점들을 모두 추가했다면 이함수를 통해서 버퍼를 만듬
	void CreateBuffers();

	//파이프라인에 등록
	void BindPipeline();

	void Write(Xml::XMLDocument& doc) override {}
	void Read(Xml::XMLElement* element) override {}

	void SaveToFile(const string& saveFilePath) override;
	void LoadFromFile(const string& loadFilePath) override;

private:
	vector<VertexTexture> vertices;
	vector<uint> indices;
	VertexBuffer* vertexBuffer;
	IndexBuffer* indexBuffer;
	D3D11_PRIMITIVE_TOPOLOGY topology;
};