#pragma once

//추상클래스

class BaseShader
{
public:
	BaseShader(class Graphics* graphics);
	virtual ~BaseShader() {}

	virtual void BindPipeline() = 0;

protected:
	bool CheckShaderError(const HRESULT& hr, ID3D10Blob* error);

protected:
	class Graphics* graphics;
	string shaderFilePath; //hlsl 파일 경로
	string functionName;//셰이더 메인함수 이름(셰이더 진입점)
};