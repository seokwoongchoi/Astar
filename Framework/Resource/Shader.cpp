#include "stdafx.h"
#include "Shader.h"

Shader::Shader(Context * context)
	: IResource(context)
	, vertexShaderPath("")
	, vertexShaderFunctionName("")
	, pixelShaderPath("")
	, pixelShaderFunctionName("")
{
	vertexShader = new VertexShader(context->GetSubsystem<Graphics>());
	pixelShader = new PixelShader(context->GetSubsystem<Graphics>());
}

Shader::~Shader()
{
	SAFE_DELETE(pixelShader);
	SAFE_DELETE(vertexShader);
}

void Shader::CreateVertexShader(const string & filePath, const string & functionName)
{
	this->vertexShaderPath = filePath;
	this->vertexShaderFunctionName = functionName;

	vertexShader->CreateVertexShader(filePath, functionName);
	vertexShader->CreateInputLayout();
}

void Shader::CreatePixelShader(const string & filePath, const string & functionName)
{
	this->pixelShaderPath = filePath;
	this->pixelShaderFunctionName = functionName;

	pixelShader->CreatePixelShader(filePath, functionName);
}

void Shader::BindPipeline()
{
	vertexShader->BindPipeline();
	pixelShader->BindPipeline();
}

void Shader::SaveToFile(const string & saveFilePath)
{
}

void Shader::LoadFromFile(const string & loadFilePath)
{
	if (loadFilePath.rfind(".hlsl") != string::npos)
	{
		CreateVertexShader(loadFilePath);
		CreatePixelShader(loadFilePath);
	}
	else
	{
		//TODO : 
	}
}
