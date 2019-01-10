#pragma once

class BlendState
{
public:
	BlendState(class Graphics* graphics);
	virtual ~BlendState();

	void Create();
	void Clear();
	void BindPipeline();
	void UnbindPipeline();

	void AlphaToCoverageEnable(const bool& val);
	void BlendEnable(const bool& val);

private:
	class Graphics* graphics;

	D3D11_BLEND_DESC desc;
	ID3D11BlendState* state;
	ID3D11BlendState* backState;
};