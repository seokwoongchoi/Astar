#pragma once

class RenderTexture
{
public:
	RenderTexture(Graphics* graphics);
	virtual ~RenderTexture();

	ID3D11ShaderResourceView* GetShaderResourceView() { return srv; }

	void Create
	(
		const uint& width,
		const uint& height,
		const DXGI_FORMAT& textureFormat = DXGI_FORMAT_R32G32B32A32_FLOAT
	);
	void Clear(const D3DXCOLOR& color = D3DXCOLOR(1, 1, 1, 1));
	void Clear(const float& r, const float& g, const float&b, const float& a = 1.0f);
	void SetRenderTarget();
	void Save(const string& saveFilePath);

private:
	Graphics* graphics;
	ID3D11Texture2D* rtvTexture;
	ID3D11RenderTargetView* rtv;
	ID3D11ShaderResourceView* srv;
	D3D11_VIEWPORT viewport;
};