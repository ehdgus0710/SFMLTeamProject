#pragma once

#include "SaveData.h"

class SaveLoadManager : public Singleton<SaveLoadManager>
{
	friend class Singleton<SaveLoadManager>;

protected:
	std::string tempSavePath = "save2.json";

public:
	void Save(const SaveDataVC& saveData);
	SaveDataVC Load();

	void Save(const SaveDataVC& saveData, const std::string& savePath);
	SaveDataVC Load(const std::string& loadPath);
protected:
	SaveLoadManager() = default;
	virtual ~SaveLoadManager();
	SaveLoadManager(const SaveLoadManager& other) = delete;
	SaveLoadManager& operator=(const SaveLoadManager& other) = delete;
};