#pragma once
#include "IResource.h"
//���� ������, ���ؽ� ����, �ε������۸� ��Ƽ� �����ϴ� Ŭ����
class Mesh : public IResource
{
public:
	Mesh(class Context* context);
	virtual ~Mesh();
	
	VertexBuffer* GetVertexBuffer()const { return vertexBuffer; }

	//Gatter �Լ�
	const vector<VertexTexture>& GetVertices() const { return vertices; }
	const vector<uint>& GetIndices() const { return indices; }
	VertexTexture const* GetVerticesPtr() const { return vertices.data(); }
	uint const* GetIndicesPtr() const { return indices.data(); }
	const uint GetVertexCount() const { return vertices.size(); }
	const uint GetIndexCount() const { return indices.size(); }


	void SetTopology(const D3D11_PRIMITIVE_TOPOLOGY& topology) { this->topology = topology; }
	
	//���� ������ �ϳ��� �߰��ϴ� �Լ�
	void AddVertex(const VertexTexture& vertex) { vertices.push_back(vertex); }
	//�ε��� ������ �ϳ��� �߰��ϴ� �Լ�
	void AddIndex(const uint& index) { indices.push_back(index); }
	
	//����� ������ �ѱ�� ��
	void AddVertices(const vector<VertexTexture>& val);
	void AddIndices(const vector<uint>& val);

	//���� �߰��� �������� ��� �߰��ߴٸ� ���Լ��� ���ؼ� ���۸� ����
	void CreateBuffers();

	//���������ο� ���
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