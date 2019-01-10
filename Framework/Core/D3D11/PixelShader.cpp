#include "stdafx.h"
#include "PixelShader.h"

PixelShader::PixelShader(Graphics * graphics)
	: BaseShader(graphics)
	, pixelShader(nullptr)
{
}

PixelShader::~PixelShader()
{
	SAFE_RELEASE(pixelShader);
}

void PixelShader::CreatePixelShader(const string & shaderFilePath, const string & functionName)
{
	this->shaderFilePath = shaderFilePath;
	this->functionName = functionName;

	ID3D10Blob* error, *blob;
	HRESULT hr = D3DX11CompileFromFileA
	(
		shaderFilePath.c_str(),
		nullptr,
		nullptr,
		functionName.c_str(),
		"ps_5_0",
		D3D10_SHADER_ENABLE_STRICTNESS,
		0,
		nullptr,
		&blob,
		&error,
		nullptr
	);
	assert(CheckShaderError(hr, error));

	hr = graphics->GetDevice()->CreatePixelShader
	(
		blob->GetBufferPointer(),
		blob->GetBufferSize(),
		nullptr,
		&pixelShader
	);
	assert(SUCCEEDED(hr));

	SAFE_RELEASE(blob);
	SAFE_RELEASE(error);
}

void PixelShader::BindPipeline()
{
	graphics->GetDeviceContext()->PSSetShader(pixelShader, nullptr, 0);
}
