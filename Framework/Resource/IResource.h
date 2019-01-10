#pragma once
#include "stdafx.h"

enum class ResourceType : uint
{
	Unknown,
	Texture,
	Shader,
	Mesh,
	Animation,
	Audio,
};

class IResource
{
public:
	template <typename T>
	static ResourceType DeduceResourceType();

public:
	IResource(class Context* context)
		: context(context)
	{
		resourceManager = context->GetSubsystem<ResourceManager>();
	}
	virtual ~IResource() {}

	const string& GetResourceName() const { return name; }
	const string& GetResourcePath() const { return filePath; }
	const ResourceType& GetResourceType() const { return type; }

	void SetResourceName(const string& name) { this->name = name; }
	void SetResourcePath(const string& path) { this->filePath = path; }
	void SetResourceType(const ResourceType& type) { this->type = type; }

	virtual void Write(Xml::XMLDocument& doc) = 0;
	virtual void Read(Xml::XMLElement* element) = 0;

	virtual void SaveToFile(const string& saveFilePath)
	{
		Xml::XMLDocument doc;
		Xml::XMLDeclaration* decl = doc.NewDeclaration();
		doc.LinkEndChild(decl);
		Write(doc);
		doc.SaveFile(saveFilePath.c_str());
	}
	virtual void LoadFromFile(const string& loadFilePath)
	{
		Xml::XMLDocument doc;
		Xml::XMLError error = doc.LoadFile(loadFilePath.c_str());
		assert(error == Xml::XMLError::XML_SUCCESS);
		Xml::XMLElement* root = doc.FirstChildElement();
		Read(root);
	}

protected:
	class Context* context;
	class ResourceManager* resourceManager;

	string name;
	string filePath;
	ResourceType type;
};

template<typename T>
inline ResourceType IResource::DeduceResourceType()
{
	//Texture2D --> class Texture2D
	string id = typeid(T).name();
	
	ResourceType enumType = ResourceType::Unknown;

	if (id.find("Texture") != string::npos)			enumType = ResourceType::Texture;
	else if (id.find("Shader") != string::npos)		enumType = ResourceType::Shader;
	else if (id.find("Mesh") != string::npos)		enumType = ResourceType::Mesh;
	else if (id.find("Animation") != string::npos)	enumType = ResourceType::Animation;
	else if (id.find("Audio") != string::npos)		enumType = ResourceType::Audio;

	return enumType;
}
