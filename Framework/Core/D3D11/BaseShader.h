#pragma once

//�߻�Ŭ����

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
	string shaderFilePath; //hlsl ���� ���
	string functionName;//���̴� �����Լ� �̸�(���̴� ������)
};