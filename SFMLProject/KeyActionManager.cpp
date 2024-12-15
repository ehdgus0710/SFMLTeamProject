#include "stdafx.h"
#include "KeyActionManager.h"

#include "rapidcsv.h"

KeyActionManager::KeyActionManager()
	: filePath("data/keySetting.csv")
{
	ResetActionKey();
}


void KeyActionManager::Init()
{
	InitEventMap();
	LoadCSV();
}

void KeyActionManager::Relaese()
{
}

void KeyActionManager::InitEventMap()
{
	for (int i = 0; i < (int)ActionKeyType::end; ++i)
	{
		switch ((ActionKeyType)i)
		{
		case ActionKeyType::LeftMove:
		{
			changeActionKeyEventMaps.insert({ ActionKeyType::LeftMove ,nullptr });
		}
		break;
		case ActionKeyType::RightMove:
			changeActionKeyEventMaps.insert({ ActionKeyType::RightMove ,nullptr });
			break;
		case ActionKeyType::Dash:
			changeActionKeyEventMaps.insert({ ActionKeyType::Dash ,nullptr });
			break;
		case ActionKeyType::Attack:
			changeActionKeyEventMaps.insert({ ActionKeyType::Attack ,nullptr });
			break;
		case ActionKeyType::Skill1:
			changeActionKeyEventMaps.insert({ ActionKeyType::Skill1 ,nullptr });
			break;
		case ActionKeyType::Skill2:
			changeActionKeyEventMaps.insert({ ActionKeyType::Skill2 ,nullptr });
			break;
		case ActionKeyType::Jump:
			changeActionKeyEventMaps.insert({ ActionKeyType::Jump ,nullptr });
			break;
		case ActionKeyType::ChangeSkul:
			changeActionKeyEventMaps.insert({ ActionKeyType::ChangeSkul ,nullptr });
			break;
		case ActionKeyType::Item:
			changeActionKeyEventMaps.insert({ ActionKeyType::Item ,nullptr });
			break;
		case ActionKeyType::end:
			break;
		default:
			break;
		}
	}
}

bool KeyActionManager::ChangeActionKey(const ActionKeyType& actionType, const sf::Keyboard::Key& changeKey)
{
	auto iter = mappingActionKeyMaps.find(actionType);
	if (iter == mappingActionKeyMaps.end())
		return false;

	for (auto changeIter = mappingActionKeyMaps.begin(); changeIter != mappingActionKeyMaps.end(); ++changeIter)
	{
		if (changeIter == iter)
			continue;

		if (changeIter->second == changeKey)
		{
			changeIter->second = iter->second;

			if (changeActionKeyEventMaps[changeIter->first])
				changeActionKeyEventMaps[changeIter->first](changeIter->second);
			break;
		}
	}

	iter->second = changeKey;

	if (changeActionKeyEventMaps[iter->first])
		changeActionKeyEventMaps[iter->first](changeKey);
	InputManager::GetInstance().BindKey(changeKey);
	
	return SaveCSV();
}

void KeyActionManager::SetChangeActionKeyEvent(const ActionKeyType& actionType, std::function<void(sf::Keyboard::Key)> changeEvent)
{
	if (changeActionKeyEventMaps.find(actionType) == changeActionKeyEventMaps.end())
		return;

	changeActionKeyEventMaps[actionType] = changeEvent;
}

void KeyActionManager::ResetActionKey()
{
	mappingActionKeyMaps.clear();

	for (int i = 0; i < (int)ActionKeyType::end; ++i)
	{
		switch ((ActionKeyType)i)
		{
		case ActionKeyType::LeftMove:
		{
			mappingActionKeyMaps.insert({ ActionKeyType::LeftMove , sf::Keyboard::Key::Left });
			InputManager::GetInstance().BindKey(sf::Keyboard::Key::Left);
		}
			break;
		case ActionKeyType::RightMove:
			mappingActionKeyMaps.insert({ ActionKeyType::RightMove , sf::Keyboard::Key::Right });
			InputManager::GetInstance().BindKey(sf::Keyboard::Key::Right);
			break;
		case ActionKeyType::Dash:
			mappingActionKeyMaps.insert({ ActionKeyType::Dash , sf::Keyboard::Key::Z });
			InputManager::GetInstance().BindKey(sf::Keyboard::Key::Z);
			break;
		case ActionKeyType::Attack:
			mappingActionKeyMaps.insert({ ActionKeyType::Attack , sf::Keyboard::Key::X });
			InputManager::GetInstance().BindKey(sf::Keyboard::Key::X);
			break;
		case ActionKeyType::Skill1:
			mappingActionKeyMaps.insert({ ActionKeyType::Skill1 , sf::Keyboard::Key::A });
			InputManager::GetInstance().BindKey(sf::Keyboard::Key::A);
			break;
		case ActionKeyType::Skill2:
			mappingActionKeyMaps.insert({ ActionKeyType::Skill2 , sf::Keyboard::Key::S });
			InputManager::GetInstance().BindKey(sf::Keyboard::Key::S);
			break;
		case ActionKeyType::Jump:
			mappingActionKeyMaps.insert({ ActionKeyType::Jump , sf::Keyboard::Key::C });
			InputManager::GetInstance().BindKey(sf::Keyboard::Key::C);
			break;
		case ActionKeyType::ChangeSkul:
			mappingActionKeyMaps.insert({ ActionKeyType::ChangeSkul , sf::Keyboard::Key::Space });
			InputManager::GetInstance().BindKey(sf::Keyboard::Key::Space);
			break;
		case ActionKeyType::Item:
			mappingActionKeyMaps.insert({ ActionKeyType::Item , sf::Keyboard::Key::V });
			InputManager::GetInstance().BindKey(sf::Keyboard::Key::V);
			break;
		case ActionKeyType::end:
			break;
		default:
			break;
		}
	}

	SaveCSV();
}

bool KeyActionManager::GetKey(const ActionKeyType& actionType)
{
	return InputManager::GetInstance().GetKey(mappingActionKeyMaps[actionType]);
}

bool KeyActionManager::GetKeyDown(const ActionKeyType& actionType)
{
	return InputManager::GetInstance().GetKeyDown(mappingActionKeyMaps[actionType]);
}

bool KeyActionManager::GetKeyPressed(const ActionKeyType& actionType)
{
	return InputManager::GetInstance().GetKeyPressed(mappingActionKeyMaps[actionType]);
}

bool KeyActionManager::GetKeyUp(const ActionKeyType& actionType)
{
	return InputManager::GetInstance().GetKeyUp(mappingActionKeyMaps[actionType]);
}

bool KeyActionManager::GetKeyNone(const ActionKeyType& actionType)
{
	return InputManager::GetInstance().GetKeyNone(mappingActionKeyMaps[actionType]);
}

const sf::Keyboard::Key KeyActionManager::GetActionKey(const ActionKeyType& actionType)
{
	auto iter = mappingActionKeyMaps.find(actionType);
	if (iter == mappingActionKeyMaps.end())
		return sf::Keyboard::Unknown;

	return iter->second;
}

bool KeyActionManager::SaveCSV()
{
	std::ofstream outFile(filePath);

	outFile << "KeyActionType,KeyboradKey" << std::endl;

	for (auto iter : mappingActionKeyMaps)
	{
		/*switch (iter.first)
		{
		case KeyActionType::LeftMove:
		{
			outFile << (int)iter.first  << "," << (int)iter.second << std::endl;
		}
		break;
		case KeyActionType::RightMove:

			break;
		case KeyActionType::Dash:

			break;
		case KeyActionType::Attack:

			break;
		case KeyActionType::Skill1:

			break;
		case KeyActionType::Skill2:

			break;
		case KeyActionType::Jump:

			break;
		case KeyActionType::ChangeSkul:

			break;
		case KeyActionType::Item:

			break;
		case KeyActionType::end:
			break;
		default:
			break;
		}*/

		outFile << (int)iter.first << "," << (int)iter.second << std::endl;
	}

	return true;
}

void KeyActionManager::LoadCSV()
{
	std::ifstream outFile(filePath);
	if (!outFile)
	{
		SaveCSV();
		return;
	}

	mappingActionKeyMaps.clear();

	rapidcsv::Document doc(filePath);

	int keyCount = doc.GetRowCount();
	for (int i = 0; i < keyCount; ++i)
	{
		mappingActionKeyMaps.insert({ (ActionKeyType)(doc.GetCell<int>(0, i)), (sf::Keyboard::Key)doc.GetCell<int>(1, i) });
		InputManager::GetInstance().BindKey((sf::Keyboard::Key)doc.GetCell<int>(1, i));
	}
}
