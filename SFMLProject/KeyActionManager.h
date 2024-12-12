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
//
//static const std::string GetName(const sf::Keyboard::Key& key)
//{
//
//
//
//    return "Unknown"
//        return "A"
//        return "B"
//        return "C"
//        return "D"
//        return "E"
//        return "F"
//        return "G"
//        return "H"
//        return "I"
//        return "J"
//        return "K"
//        return "L"
//        return "M"
//        return "N"
//        return "O"
//        return "P"
//        return "Q"
//        return "R"
//        return "S"
//        return "T"
//        return "U"
//        return "V"
//        return "W"
//        return "X"
//        return "Y"
//        return "Z"
//        return "Num0"
//        return "Num1"
//        return "Num2"
//        return "Num3"
//        return "Num4"
//        return "Num5"
//        return "Num6"
//        return "Num7"
//        return "Num8"
//        return "Num9"
//        return "Escape,     "
//        return "LControl,   "
//        return "LShift,     "
//        return "LAlt,      "
//        return "LSystem,   "
//        return "RControl,  "
//        return "RShift,    "
//        return "RAlt,      "
//        return "RSystem,   "
//        return "Menu,      "
//        return "LBracket,   "
//        return "RBracket,   "
//        return "Semicolon,  "
//        return "Comma,      "
//        return "Period,     "
//        return "Apostrophe, "
//        return "Slash,      "
//        return "Backslash,  "
//        return "Grave,      "
//        return "Equal,      "
//        return "Hyphen,     "
//        return "Space,      "
//        return "Enter,      "
//        return "Backspace,  "
//        return "Tab,        "
//        return "PageUp,     "
//        return "PageDown,   "
//        return "End,        "
//        return "Home,       "
//        return "Insert,     "
//        return "Delete,     "
//        return "Add,        "
//        return "Subtract,   "
//        return "Multiply,   "
//        return "Divide,     "
//        return "Left,       "
//        return "Right,      "
//        return "Up"
//        return "Down"
//        return "Numpad0"
//        return "Numpad1"
//        return "Numpad2"
//        return "Numpad3"
//        return "Numpad4"
//        return "Numpad5"
//        return "Numpad6"
//        return "Numpad7"
//        return "Numpad8"
//        return "Numpad9"
//        return "F1"
//        return "F2"
//        return "F3"
//        return "F4"
//        return "F5"
//        return "F6"
//        return "F7"
//        return "F8"
//        return "F9"
//        return "F10"
//        return "F11"
//        return "F12"
//        return "F13"
//        return "F14"
//        return "F15"
//        return "Pause"
//        return "KeyCount"
//}