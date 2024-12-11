#include "stdafx.h"
#include "KeyActionManager.h"

#include "rapidcsv.h"

KeyActionManager::KeyActionManager()
	: filePath("data/keySetting.csv")
{
	ResetKeyAction();
}


void KeyActionManager::Init()
{
	LoadCSV();
}

void KeyActionManager::Relaese()
{
}

bool KeyActionManager::ChangeKeyAction(const KeyActionType& actionType, const sf::Keyboard::Key& changeKey)
{
	auto iter = mappingKeyActionMaps.find(actionType);
	if (iter == mappingKeyActionMaps.end())
		return false;

	for (auto changeIter = mappingKeyActionMaps.begin(); changeIter != mappingKeyActionMaps.end(); ++iter)
	{
		if (changeIter == iter)
			continue;

		if (changeIter->second == changeKey)
		{
			changeIter->second = iter->second;
			break;
		}
	}

	iter->second = changeKey;
	InputManager::GetInstance().BindKey(changeKey);
	
	return SaveCSV();
}

void KeyActionManager::ResetKeyAction()
{
	mappingKeyActionMaps.clear();

	for (int i = 0; i < (int)KeyActionType::end; ++i)
	{
		switch ((KeyActionType)i)
		{
		case KeyActionType::LeftMove:
		{
			mappingKeyActionMaps.insert({ KeyActionType::LeftMove , sf::Keyboard::Key::Left });
			InputManager::GetInstance().BindKey(sf::Keyboard::Key::Left);
		}
			break;
		case KeyActionType::RightMove:
			mappingKeyActionMaps.insert({ KeyActionType::RightMove , sf::Keyboard::Key::Right });
			InputManager::GetInstance().BindKey(sf::Keyboard::Key::Right);
			break;
		case KeyActionType::Dash:
			mappingKeyActionMaps.insert({ KeyActionType::Dash , sf::Keyboard::Key::Z });
			InputManager::GetInstance().BindKey(sf::Keyboard::Key::Z);
			break;
		case KeyActionType::Attack:
			mappingKeyActionMaps.insert({ KeyActionType::Attack , sf::Keyboard::Key::X });
			InputManager::GetInstance().BindKey(sf::Keyboard::Key::X);
			break;
		case KeyActionType::Skill1:
			mappingKeyActionMaps.insert({ KeyActionType::Skill1 , sf::Keyboard::Key::A });
			InputManager::GetInstance().BindKey(sf::Keyboard::Key::A);
			break;
		case KeyActionType::Skill2:
			mappingKeyActionMaps.insert({ KeyActionType::Skill2 , sf::Keyboard::Key::S });
			InputManager::GetInstance().BindKey(sf::Keyboard::Key::S);
			break;
		case KeyActionType::Jump:
			mappingKeyActionMaps.insert({ KeyActionType::Jump , sf::Keyboard::Key::C });
			InputManager::GetInstance().BindKey(sf::Keyboard::Key::C);
			break;
		case KeyActionType::ChangeSkul:
			mappingKeyActionMaps.insert({ KeyActionType::ChangeSkul , sf::Keyboard::Key::Space });
			InputManager::GetInstance().BindKey(sf::Keyboard::Key::Space);
			break;
		case KeyActionType::Item:
			mappingKeyActionMaps.insert({ KeyActionType::Item , sf::Keyboard::Key::V });
			InputManager::GetInstance().BindKey(sf::Keyboard::Key::V);
			break;
		case KeyActionType::end:
			break;
		default:
			break;
		}
	}
	
}

bool KeyActionManager::GetKey(const KeyActionType& actionType)
{
	return InputManager::GetInstance().GetKey(mappingKeyActionMaps[actionType]);
}

bool KeyActionManager::GetKeyDown(const KeyActionType& actionType)
{
	return InputManager::GetInstance().GetKeyDown(mappingKeyActionMaps[actionType]);
}

bool KeyActionManager::GetKeyPressed(const KeyActionType& actionType)
{
	return InputManager::GetInstance().GetKeyPressed(mappingKeyActionMaps[actionType]);
}

bool KeyActionManager::GetKeyUp(const KeyActionType& actionType)
{
	return InputManager::GetInstance().GetKeyUp(mappingKeyActionMaps[actionType]);
}

bool KeyActionManager::GetKeyNone(const KeyActionType& actionType)
{
	return InputManager::GetInstance().GetKeyNone(mappingKeyActionMaps[actionType]);
}

bool KeyActionManager::SaveCSV()
{
	return false;
}

void KeyActionManager::LoadCSV()
{
	std::ofstream outFile(filePath);
	if (!outFile)
		return;

	rapidcsv::Document doc(filePath);
}
