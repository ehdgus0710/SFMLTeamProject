#pragma once
#include "Entity.h"

template <typename T>
class Resources : public Entity
{
	template <typename U>
	friend class ResourcesManager;
private:
	std::string key;
	std::string filePath;
	T* resource;
	bool isNotUnload;

public:
	bool Save() const override;
	bool Load() override;
	bool SaveCsv(const std::string& filePath) const override;
	bool LoadCsv(const std::string& filePath) override;
	void SetKey(const std::string key)
	{
		this->key = key;
	}
	const std::string& GetKey() { return key; }

	void SetFilePath(const std::string path)
	{
		this->filePath = path;
	}
	const std::string& GetFilePath() { return filePath; }

	void SetnotUnload(bool notUnload)
	{
		isNotUnload = notUnload;
	}

	bool IsNotUnload()
	{
		return isNotUnload;
	}

	T& GetResource() { return *resource; }

public:
	Resources();
	~Resources();
};

template<typename T>
inline bool Resources<T>::Save() const
{
	return true;
}

template<typename T>
inline bool Resources<T>::Load()
{
	return true;
}

template<typename T>
inline bool Resources<T>::SaveCsv(const std::string& filePath) const
{
	return false;
}

template<typename T>
inline bool Resources<T>::LoadCsv(const std::string& filePath)
{
	return false;
}

template<typename T>
inline Resources<T>::Resources()
	: isNotUnload(false)
{
	resource = new T;
}

template<typename T>
inline Resources<T>::~Resources()
{
	delete resource;
}
