#pragma once

class KeyActionManager : public Singleton<KeyActionManager>
{
	friend Singleton<KeyActionManager>;
private:
	std::unordered_map<ActionKeyType, sf::Keyboard::Key>						mappingActionKeyMaps;
	std::unordered_map<ActionKeyType, std::function<void(sf::Keyboard::Key)>>	changeActionKeyEventMaps;
	std::string filePath;

private:
	void InitEventMap();

public:
	bool ChangeActionKey(const ActionKeyType& actionType, const sf::Keyboard::Key& changeKey);
	void SetChangeActionKeyEvent(const ActionKeyType& actionType, std::function<void(sf::Keyboard::Key)> changeEvent);
	void ResetActionKey();

	bool GetKey(const ActionKeyType& actionType);
	bool GetKeyDown(const ActionKeyType& actionType);
	bool GetKeyPressed(const ActionKeyType& actionType);
	bool GetKeyUp(const ActionKeyType& actionType);
	bool GetKeyNone(const ActionKeyType& actionType);

	const sf::Keyboard::Key GetActionKey(const ActionKeyType& actionType);
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