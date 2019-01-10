#pragma once
#include "IResource.h"

class Shader : public IResource
{
public:
	Shader(class Context* context);
	virtual ~Shader();

	void CreateVertexShader
	(
		const string& filePath, 
		const string& functionName = "VS"
	);

	void CreatePixelShader
	(
		const string& filePath,
		const string& functionName = "PS"
	);

	void BindPipeline();

	void Write(Xml::XMLDocument& doc) override {}
	void Read(Xml::XMLElement* element) override {}

	void SaveToFile(const string & saveFilePath) override;
	void LoadFromFile(const string & loadFilePath) override;

private:
	string vertexShaderPath;
	string vertexShaderFunctionName;
	string pixelShaderPath;
	string pixelShaderFunctionName;

	VertexShader* vertexShader;
	PixelShader* pixelShader;
};