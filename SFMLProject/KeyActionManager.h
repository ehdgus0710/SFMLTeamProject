#pragma once

class KeyActionManager : public Singleton<KeyActionManager>
{
	friend Singleton<KeyActionManager>;
private:
	std::unordered_map<KeyActionType, sf::Keyboard::Key> mappingKeyActionMaps;
	std::string filePath;

public:
	bool ChangeKeyAction(const KeyActionType& actionType, const sf::Keyboard::Key& changeKey);
	void ResetKeyAction();

	bool GetKey(const KeyActionType& actionType);
	bool GetKeyDown(const KeyActionType& actionType);
	bool GetKeyPressed(const KeyActionType& actionType);
	bool GetKeyUp(const KeyActionType& actionType);
	bool GetKeyNone(const KeyActionType& actionType);

public:
	void Init();
	void Relaese();

	void LoadCSV();
	bool SaveCSV();
protected:
	KeyActionManager();
	~KeyActionManager() = default;
	KeyActionManager(const KeyActionManager&) = delete;
	KeyActionManager& operator=(const KeyActionManager&) = delete;
};