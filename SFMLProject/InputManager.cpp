#include "stdafx.h"

inline void InputManager::Clear()
{
	keyboardInputMap.clear();
	mouseInputMap.clear();
}

void InputManager::SetInputable(bool active)
{
	isInputable = active;

	if (isInputable)
	{
		for (auto& pair : axisInfoMap)
		{
			auto& axisInfo = pair.second;
			axisInfo.value = 0.f;
		}
	}
}

InputManager::InputManager()
	: isInputable(false)
{
}

bool InputManager::BindKey(const sf::Keyboard::Key& key)
{
	auto iter = keyboardInputMap.find(key);

	if (iter != keyboardInputMap.end())
		return false;

	keyboardInputMap.insert({ key , KeyState::KeyNone });
	return true;
}

bool InputManager::BindMouseButton(const sf::Mouse::Button& mouseButton)
{
	auto iter = mouseInputMap.find(mouseButton);
	
	if (iter != mouseInputMap.end())
		return false;

	mouseInputMap.insert({ mouseButton , KeyState::KeyNone });
	return true;
}

void InputManager::UpDownCheck()
{
	int size = (int)keyUpDownStateVector.size();
	for (int i = 0; i < size; ++i)
	{
		if(keyboardInputMap[keyUpDownStateVector[i]] == KeyState::KeyDown)
			keyboardInputMap[keyUpDownStateVector[i]] = KeyState::KeyPressed;
		else
			keyboardInputMap[keyUpDownStateVector[i]] = KeyState::KeyNone;
	}

	size = (int)mouseUpDownStateVector.size();
	for (int i = 0; i < size; ++i)
	{
		if (mouseInputMap[mouseUpDownStateVector[i]] == KeyState::KeyDown)
			mouseInputMap[mouseUpDownStateVector[i]] = KeyState::KeyPressed;
		else
			mouseInputMap[mouseUpDownStateVector[i]] = KeyState::KeyNone;
	}

	keyUpDownStateVector.clear();
	mouseUpDownStateVector.clear();
}

void InputManager::Init()
{
	isInputable = false;

	AxisInfo infoHorizontal;
	infoHorizontal.axis = Axis::Horizontal;
	infoHorizontal.AddKey(true, sf::Keyboard::D);
	infoHorizontal.AddKey(true, sf::Keyboard::Right);
	infoHorizontal.AddKey(false, sf::Keyboard::A);
	infoHorizontal.AddKey(false, sf::Keyboard::Left);
	axisInfoMap.insert({ Axis::Horizontal, infoHorizontal });

	AxisInfo infoVertical;
	infoVertical.axis = Axis::Vertical;
	infoVertical.AddKey(true, sf::Keyboard::S);	
	infoVertical.AddKey(true, sf::Keyboard::Down);
	infoVertical.AddKey(false, sf::Keyboard::W);
	infoVertical.AddKey(false, sf::Keyboard::Up);
	axisInfoMap.insert({ Axis::Vertical, infoVertical });

	AxisInfo infoJump;
	infoJump.axis = Axis::Jump;
	infoJump.AddKey(true, sf::Keyboard::Space);
	infoJump.sensi = 7.f;
	axisInfoMap.insert({ Axis::Jump, infoJump });

	BindKey(sf::Keyboard::Up);
	BindKey(sf::Keyboard::Down);
	BindKey(sf::Keyboard::Right);
	BindKey(sf::Keyboard::Left);
	BindKey(sf::Keyboard::Space);
	BindKey(sf::Keyboard::LShift);

	BindKey(sf::Keyboard::Z);
	BindKey(sf::Keyboard::X);
	BindKey(sf::Keyboard::C);

	BindKey(sf::Keyboard::A);
	BindKey(sf::Keyboard::S);

	BindKey(sf::Keyboard::F11);
	BindKey(sf::Keyboard::F3);
	BindKey(sf::Keyboard::F2);
	BindKey(sf::Keyboard::F4);

	BindMouseButton(sf::Mouse::Left);
	BindMouseButton(sf::Mouse::Right);
}

void InputManager::UpdateEvent(const sf::Event* ev)
{
	switch (ev->type)
	{
	case sf::Event::KeyPressed:
	{
		if (GetKey(ev->key.code))
		{
			keyboardInputMap[ev->key.code] = KeyState::KeyDown;
			keyUpDownStateVector.push_back(ev->key.code);
		}
	}
	break;
	case sf::Event::KeyReleased:
	{
		if (GetKey(ev->key.code))
		{
			keyboardInputMap[ev->key.code] = KeyState::KeyUp;
			keyUpDownStateVector.push_back(ev->key.code);
		}
	}
	break;
	case sf::Event::MouseButtonPressed:
	{
		if ((GetKey(ev->mouseButton.button)))
		{
			mouseInputMap[ev->mouseButton.button] = KeyState::KeyDown;
			mouseUpDownStateVector.push_back(ev->mouseButton.button);
		}
	}
	break;
	case sf::Event::MouseButtonReleased:
	{
		if ((GetKey(ev->mouseButton.button)))
		{
			mouseInputMap[ev->mouseButton.button] = KeyState::KeyUp;
			mouseUpDownStateVector.push_back(ev->mouseButton.button);
		}
	}
		break;
	case sf::Event::MouseMoved:
		mousePosition = sf::Mouse::getPosition(*WindowManager::GetInstance().GetRenderWindow());
		break;
	}
}

void InputManager::Update(float deltaTime)
{
	if (isInputable)
		return;

	for (auto& pair : axisInfoMap)
	{
		auto& axisInfo = pair.second;
		float raw = GetAxisRaw(axisInfo.axis);
		float dir = raw;

		if (dir == 0.f && axisInfo.value != 0.f)
		{
			dir = axisInfo.value > 0.f ? -1.f : 1.f;
		}

		axisInfo.value += dir * axisInfo.sensi * deltaTime;
		axisInfo.value = Utils::Clamp(axisInfo.value, -1.f, 1.f);

		float stopThreshold = std::abs(dir * axisInfo.sensi * deltaTime);
		if (raw == 0.f && std::abs(axisInfo.value) < stopThreshold)
		{
			axisInfo.value = 0.f;
		}
	}
}

bool InputManager::GetKey(const sf::Keyboard::Key& key)
{
	return keyboardInputMap.find(key) != keyboardInputMap.end();
}

bool InputManager::GetKeyDown(const sf::Keyboard::Key& key)
{
	if (!GetKey(key))
		return false;

	return  keyboardInputMap[key] == KeyState::KeyDown;
}

bool InputManager::GetKeyPressed(const sf::Keyboard::Key& key)
{
	if (!GetKey(key))
		return false;

	return  keyboardInputMap[key] == KeyState::KeyPressed;
}

bool InputManager::GetKeyUp(const sf::Keyboard::Key& key)
{
	if (!GetKey(key))
		return false;

	return keyboardInputMap[key] == KeyState::KeyUp;
}

bool InputManager::GetKey(const sf::Mouse::Button& button)
{
	return mouseInputMap.find(button) != mouseInputMap.end();
}

bool InputManager::GetKeyDown(const sf::Mouse::Button& button)
{
	if (!GetKey(button))
		return false;

	return mouseInputMap[button] == KeyState::KeyDown;
}

bool InputManager::GetKeyPressed(const sf::Mouse::Button& button)
{
	if (!GetKey(button))
		return false;

	return mouseInputMap[button] == KeyState::KeyPressed;
}

bool InputManager::GetKeyUp(const sf::Mouse::Button& button)
{
	if (!GetKey(button))
		return false;

	return mouseInputMap[button] == KeyState::KeyUp;
}

float InputManager::GetAxisRaw(Axis axis)
{
	auto findIter = axisInfoMap.find(axis);

	if (findIter == axisInfoMap.end())
	{
		return 0.0f;
	}

	auto& axisInfo = findIter->second;
	bool isNegative = false;
	bool isPositivies = false;

	for (auto& negative : axisInfo.negativesVector)
	{
		auto iter = keyboardInputMap.find(negative);
		if (iter != keyboardInputMap.end() && iter->second == KeyState::KeyPressed)
			isNegative = true;
	}

	for (auto& positivies : axisInfo.positiviesVector)
	{
		auto iter = keyboardInputMap.find(positivies);
		if (iter != keyboardInputMap.end() && iter->second == KeyState::KeyPressed)
			isPositivies = true;
	}

	if (isPositivies && isNegative || !isPositivies && !isNegative)
		return 0.0f;
	else if (isPositivies)
		return 1.f;
	else
		return -1.f;

}

float InputManager::GetAxis(Axis axis)
{
	auto findIter = axisInfoMap.find(axis);

	if (findIter == axisInfoMap.end())
	{
		return 0.0f;
	}
	return findIter->second.value;
}

const sf::Vector2i InputManager::GetMousePosition() const
{
	return mousePosition;
}
