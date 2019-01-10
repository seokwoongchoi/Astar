#include "stdafx.h"
#include "Texture2D.h"

Texture2D::Texture2D(Context * context)
	: IResource(context)
	, texture(nullptr)
	, srv(nullptr)
{
	graphics = context->GetSubsystem<Graphics>();

	ZeroMemory(&textureDesc, sizeof(D3D11_TEXTURE2D_DESC));
	ZeroMemory(&srvDesc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
}

Texture2D::~Texture2D()
{
	SAFE_RELEASE(srv);
	SAFE_RELEASE(texture);
}

const D3DXVECTOR2 Texture2D::GetSize() const
{
	return D3DXVECTOR2
	(
		GetWidth(),
		GetHeight()
	);
}

void Texture2D::SetVS(const uint & startSlot)
{
	assert(graphics);
	graphics->GetDeviceContext()->VSSetShaderResources(startSlot, 1, &srv);
}

void Texture2D::SetPS(const uint & startSlot)
{
	assert(graphics);
	graphics->GetDeviceContext()->PSSetShaderResources(startSlot, 1, &srv);
}

void Texture2D::CreateTextureFromFile(const string & filePath)
{
	this->filePath = filePath;
	//이미 완성된 텍스쳐가 존재할때 원본 만드는 과정을 건너띄고 바로 srv를 만들어줌
	HRESULT hr = D3DX11CreateShaderResourceViewFromFileA
	(
		graphics->GetDevice(),
		filePath.c_str(),
		nullptr,
		nullptr,
		&srv,
		nullptr
	);
	assert(SUCCEEDED(hr));

	srv->GetDesc(&srvDesc);//srv에서 ID3D11_SHADER_RESOURCE_VIEW_DESC를 꺼내옴
	srv->GetResource(reinterpret_cast<ID3D11Resource**>(&texture)); //srv에서 원본(texture)를 꺼내옴
	texture->GetDesc(&textureDesc);//texture에서 ID3D11_TEXTURE2D_DESC 
}

void Texture2D::CreateTexture(const float & width, const float & height, const DXGI_FORMAT & format)
{
	//원본(ID3D11Texture2D :: texture)의 Desc를 만듬
	textureDesc.Width = static_cast<uint>(width);
	textureDesc.Height= static_cast<uint>(height);
	textureDesc.MipLevels = 1;
	textureDesc.ArraySize = 1;
	textureDesc.Format = format;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.SampleDesc.Quality = 0;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = 0;

	//원본을 만듬
	HRESULT hr = graphics->GetDevice()->CreateTexture2D
	(
		&textureDesc, 
		nullptr, 
		&texture
	);
	assert(SUCCEEDED(hr));

	//srv의 Desc를 만듬
	srvDesc.Format = format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = 1;

	//원본과 srv의 Desc를 가지고 srv를 만듬
	hr = graphics->GetDevice()->CreateShaderResourceView
	(
		texture, 
		&srvDesc, 
		&srv
	);
	assert(SUCCEEDED(hr));
}

void Texture2D::SaveToFile(const string & saveFilePath)
{
	//TODO : Xml Write Code 처리할것
}

void Texture2D::LoadFromFile(const string & loadFilePath)
{
	if (loadFilePath.rfind(".xml") != string::npos)
	{
		//TODO : 
	}
	else
		CreateTextureFromFile(loadFilePath);
}
