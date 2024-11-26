#include "stdafx.h"
#include "SaveLoadManger.h"


void SaveLoadManager::Save(const SaveDataVC& saveData)
{
	json j = saveData;

	std::ofstream f(tempSavePath);
	f << j.dump(4) << std::endl;
	f.close();

}

SaveDataVC SaveLoadManager::Load()
{
	std::ifstream f(tempSavePath);

	json j = json::parse(f);

	int version = j["version"];

	SaveData* saveData = nullptr;

	switch (version)
	{
	case 1:
	{
		SaveDataV1 v1 = j.get<SaveDataV1>();
		saveData = new SaveDataV1(v1);
		break;
	}
	case 2:
	{
		SaveDataV2 v2 = j.get<SaveDataV2>();
		saveData = new SaveDataV2(v2);
		break;
	}
	default:
	{
		SaveDataV2 v2 = j.get<SaveDataV2>();
		saveData = new SaveDataV2(v2);
		break;
	}
	}
	f.close();

	while (saveData->version < 2)
	{
		SaveData* oldData = saveData;
		saveData = saveData->VersionUp();
		delete oldData;
	}

	SaveDataVC ret(*((SaveDataVC*)saveData));
	delete saveData;

	return ret;
}

void SaveLoadManager::Save(const SaveDataVC& saveData, const std::string& savePath)
{
	json j = saveData;

	std::ofstream f(savePath);
	f << j.dump(4) << std::endl;
	f.close();
}

SaveDataVC SaveLoadManager::Load(const std::string& loadPath)
{
	std::ifstream f(loadPath);

	json j = json::parse(f);

	int version = j["version"];

	SaveData* saveData = nullptr;

	switch (version)
	{
	case 1:
	{
		SaveDataV1 v1 = j.get<SaveDataV1>();
		saveData = new SaveDataV1(v1);
		break;
	}
	case 2:
	{
		SaveDataV2 v2 = j.get<SaveDataV2>();
		saveData = new SaveDataV2(v2);
		break;
	}
	}
	f.close();

	while (saveData->version < 2)
	{
		SaveData* oldData = saveData;
		saveData = saveData->VersionUp();
		delete oldData;
	}

	SaveDataVC ret(*((SaveDataVC*)saveData));
	delete saveData;

	return ret;
}

SaveLoadManager::~SaveLoadManager()
{
}
