#pragma once

class LineRender
{
public:
	LineRender(class Context* context);
	virtual ~LineRender();

	void AddLine
	(
		const D3DXVECTOR3& start,
		const D3DXVECTOR3& end,
		const D3DXCOLOR& color
	);
	void AddLine
	(
		const float& startX,
		const float& startY,
		const float& endX,
		const float& endY,
		const float& r,
		const float& g,
		const float& b,
		const float& a
	);
	void AddLines(const vector<VertexColor>& lines);
	void AddBoundBox(const BoundBox& box, D3DXCOLOR& color);
	void Clear();

	void Update();
	void Render();

private:
	void AddVertex(const VertexColor& vertex);
	void AddVertex(const D3DXVECTOR3& position, const D3DXCOLOR& color);
	void AddVertex
	(
		const float& x,
		const float& y,
		const float& z,
		const float& r,
		const float& g,
		const float& b,
		const float& a
	);

	void CreateVertexBuffer();
	void UpdateVertexBuffer();

private:
	class Context* context;
	class Shader* shader;
	class VertexBuffer* vertexBuffer;
	vector<VertexColor> vertices;
	uint vertexCount;
};