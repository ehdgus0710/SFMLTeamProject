#pragma once

#include "Core.h"

class KeyAction
{
private:
	KeyState keyState;
	//sf::KeyT

public:
	void SetKeyState(KeyState state) { keyState = state; }
	const KeyState& GetKeyState() const { return keyState; }

public:
	KeyAction();
	~KeyAction();
};

