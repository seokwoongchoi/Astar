#pragma once
#include "ISubsystem.h"
#include "../../Resource/IResource.h"

class ResourceManager : public ISubsystem
{
public:
	ResourceManager(class Context* context);
	virtual ~ResourceManager();

	template <typename T> T* LoadFromFile(const string& filePath);
	template <typename T> T* GetResourceFromName(const string& name);
	template <typename T> T* GetResourceFromPath(const string& path);
	template <typename T> vector<T*> GetResourceFromType();
	vector<class IResource*> GetAllResource();

	void RegistResource(class IResource* resource);
	void RegistResourceDirectory(ResourceType type, const string& directory);

	void Initialize() override {}
	void Update() override {}

private:
	typedef vector<class IResource*> ResourceGroup;
	map<ResourceType, ResourceGroup> resourceGroups;
	map<ResourceType, string> resourceDirectories;
};

template<typename T>
inline T * ResourceManager::LoadFromFile(const string & filePath)
{
	IResource* resource = GetResourceFromPath<T>(filePath);

	if (resource == nullptr)
	{
		resource = new T(context);
		resource->SetResourceType(IResource::DeduceResourceType<T>());
		resource->SetResourcePath(filePath);
		resource->SetResourceName(Path::GetIntactFileNameFromFilePath(filePath));
		resource->LoadFromFile(filePath);

		RegistResource(resource);
	}

	return static_cast<T*>(resource);
}

template<typename T>
inline T * ResourceManager::GetResourceFromName(const string & name)
{
	for (IResource* resource : resourceGroups[IResource::DeduceResourceType<T>()])
	{
		if (name == resource->GetResourceName())
			return static_cast<T*>(resource);
	}
	return nullptr;
}

template<typename T>
inline T * ResourceManager::GetResourceFromPath(const string & path)
{
	for (IResource* resource : resourceGroups[IResource::DeduceResourceType<T>()])
	{
		if (path == resource->GetResourcePath())
			return static_cast<T*>(resource);
	}
	return nullptr;
}

template<typename T>
inline vector<T*> ResourceManager::GetResourceFromType()
{
	return resourceGroups[IResource::DeduceResourceType<T>()];
}
