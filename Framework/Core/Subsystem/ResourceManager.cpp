#include "stdafx.h"
#include "ResourceManager.h"

ResourceManager::ResourceManager(Context * context)
	: ISubsystem(context)
{
	RegistResourceDirectory(ResourceType::Texture,		"../Assets/");
	RegistResourceDirectory(ResourceType::Shader,		"../Assets/");
	RegistResourceDirectory(ResourceType::Mesh,			"../Assets/");
	RegistResourceDirectory(ResourceType::Animation,	"../Assets/");
	RegistResourceDirectory(ResourceType::Audio,		"../Assets/");
}

ResourceManager::~ResourceManager()
{
	for (auto resourceGroup : resourceGroups)
	{
		for (auto resource : resourceGroup.second)
			SAFE_DELETE(resource);
	}
}

vector<class IResource*> ResourceManager::GetAllResource()
{
	return vector<class IResource*>();
}

void ResourceManager::RegistResource(IResource * resource)
{
	assert(resource);
	resourceGroups[resource->GetResourceType()].push_back(resource);
}

void ResourceManager::RegistResourceDirectory(ResourceType type, const string & directory)
{
	resourceDirectories[type] = directory;
}
