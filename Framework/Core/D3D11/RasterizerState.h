#pragma once

class RasterizerState
{
public:
	RasterizerState(class Graphics* graphics);
	virtual ~RasterizerState();

	void Create();
	void Clear();
	void BindPipeline();
	void UnbindPipeline();

	void CullMode(const D3D11_CULL_MODE& val);
	void FillMode(const D3D11_FILL_MODE& val);
	void FrontCounterClockwise(const bool& val);

private:
	class Graphics* graphics;

	D3D11_RASTERIZER_DESC desc;
	ID3D11RasterizerState* state;
	ID3D11RasterizerState* backState;
};