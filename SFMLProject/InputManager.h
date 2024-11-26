#pragma once

enum class Axis
{
	Horizontal,
	Vertical,
	Jump,
};

struct AxisInfo
{
	Axis axis;
	std::vector<sf::Keyboard::Key> positiviesVector;
	std::vector<sf::Keyboard::Key> negativesVector;
	float sensi = 2.f;			// 증가 
	float value = 0.f;			// -1 ~ 1 사이 값

	void AddKey(bool positive, sf::Keyboard::Key code)
	{
		if (positive)
		{
			positiviesVector.push_back(code);
		}
		else
		{
			negativesVector.push_back(code);
		}
	}
};

class InputManager : public Singleton<InputManager>
{
	friend Singleton<InputManager>;
private:
	std::unordered_map<sf::Keyboard::Key, KeyState> keyboardInputMap;
	std::unordered_map<sf::Mouse::Button, KeyState> mouseInputMap;
	std::unordered_map<Axis, AxisInfo>				axisInfoMap;

	std::vector<sf::Keyboard::Key>					keyUpDownStateVector;
	std::vector<sf::Mouse::Button>					mouseUpDownStateVector;
	sf::Vector2i									mousePosition;
	bool											isInputable;


public:
	bool BindKey(const sf::Keyboard::Key& key);
	bool BindMouseButton(const sf::Mouse::Button& mouseButton);

	void UpDownCheck();

	const sf::Vector2i GetMousePosition() const;

public:
	void Init();
	void UpdateEvent(const sf::Event* ev);
	void Update(float deltaTime);

	bool GetKey(const sf::Keyboard::Key& key);
	bool GetKeyDown(const sf::Keyboard::Key& key);
	bool GetKeyPressed(const sf::Keyboard::Key& key);
	bool GetKeyUp(const sf::Keyboard::Key& key);

	bool GetKey(const sf::Mouse::Button& button);
	bool GetKeyDown(const sf::Mouse::Button& button);
	bool GetKeyPressed(const sf::Mouse::Button& button);
	bool GetKeyUp(const sf::Mouse::Button& button);

	float GetAxisRaw(Axis axis);
	float GetAxis(Axis axis);

	void Clear();

	void SetInputable(bool active);
	bool GetInputable() { return isInputable; }
protected:
	InputManager();
	~InputManager() = default;
	InputManager(const InputManager&) = delete;
	InputManager& operator=(const InputManager&) = delete;
};