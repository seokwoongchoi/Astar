#pragma once

class IndexBuffer
{
public:
	IndexBuffer(class Graphics* graphics);
	virtual ~IndexBuffer();

	void Create(const vector<uint>& indices, const D3D11_USAGE& usage = D3D11_USAGE_DEFAULT);
	void Clear();

	void* Map();
	void Ummap();

	void BindPipeline();

private:
	class Graphics* graphics;
	ID3D11Buffer* ibuffer;
};