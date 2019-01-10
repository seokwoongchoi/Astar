#pragma once
#include "IResource.h"

class Texture2D : public IResource
{
public:
	Texture2D(class Context* context);
	virtual ~Texture2D();

	const string& GetFilePath() const { return filePath; }
	const D3DXVECTOR2 GetSize() const;
	const float GetWidth() const { return static_cast<float>(textureDesc.Width); }
	const float GetHeight() const { return static_cast<float>(textureDesc.Height); }

	void SetVS(const uint& startSlot);
	void SetPS(const uint& startSlot);

	void CreateTextureFromFile(const string& filePath);
	void CreateTexture(const float& width, const float& height, const DXGI_FORMAT& format);

	void Write(Xml::XMLDocument& doc) override {}
	void Read(Xml::XMLElement* element) override {}

	void SaveToFile(const string& saveFilePath);
	void LoadFromFile(const string& loadFilePath);

private:
	class Graphics* graphics;
	ID3D11Texture2D* texture;
	ID3D11ShaderResourceView* srv;
	D3D11_TEXTURE2D_DESC textureDesc;
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
};