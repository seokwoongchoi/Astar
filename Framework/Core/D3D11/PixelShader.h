#pragma once
#include "BaseShader.h"

class PixelShader : public BaseShader
{
public:
	PixelShader(class Graphics* graphics);
	virtual ~PixelShader();

	void CreatePixelShader(const string& shaderFilePath, const string& functionName = "PS");
	void BindPipeline();

private:
	ID3D11PixelShader* pixelShader;
};