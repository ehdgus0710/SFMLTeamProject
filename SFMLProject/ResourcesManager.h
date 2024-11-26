#pragma once
#include "Resources.h"
#include "Core.h"

template<typename T>
class ResourcesManager : public Singleton<ResourcesManager<T>>
{
	friend Singleton<ResourcesManager<T>>;
protected:
	std::unordered_map<std::string, Resources<T>*> resourcesMap;

	ResourcesManager() = default;
	~ResourcesManager()
	{
		UnloadAll();
	}
	ResourcesManager(const ResourcesManager&) = delete;
	ResourcesManager& operator=(const ResourcesManager&) = delete;
public:
	static T Empty;
	static Resources<T> ResourcesEmpty;

	void UnloadAll()
	{
		auto iter = resourcesMap.begin();

		while (iter != resourcesMap.end())
		{
			if (iter->second->IsNotUnload())
			{
				delete iter->second;
				iter = resourcesMap.erase(iter);
			}
			else
				++iter;
		}
	}

	bool Load(const std::string& id, const std::string& filepath, bool notUnloadAll = false)
	{
		if (resourcesMap.find(id) != resourcesMap.end())
			return false;

		Resources<T>* resource = new Resources<T>;

		bool success = resource->resource->loadFromFile(filepath);
		assert(success);

		if (success)
		{
			resourcesMap.insert({ id, resource });
			resource->SetKey(id);
			resource->SetFilePath(filepath);
			resource->SetnotUnload(notUnloadAll);
		}
		else
		{
			delete resource;
		}

		return success;
	}

	bool unLoad(const std::string& id)
	{
		auto iter = resourcesMap.find(id);

		if (iter == resourcesMap.end())
			return false;

		delete iter->second;
		resourcesMap.erase(iter);
		return true;
	}

	Resources<T>& GetResource(const std::string& id)
	{
		auto iter = resourcesMap.find(id);
		if (iter == resourcesMap.end())
		{
			return ResourcesEmpty;
		}
		return *(iter->second);
	}

	T& Get(const std::string& id)
	{
		auto iter = resourcesMap.find(id);
		if (iter == resourcesMap.end())
		{
			return Empty;
		}
		return (*iter->second->resource);
	}

	const std::unordered_map<std::string, Resources<T>*>& GetResourcesMap() { return resourcesMap; }
};

template<typename T>
T ResourcesManager<T>::Empty;
template<typename T>
Resources<T> ResourcesManager<T>::ResourcesEmpty;

#define TEXTURE_MANAGER (ResourcesManager<sf::Texture>::GetInstance())