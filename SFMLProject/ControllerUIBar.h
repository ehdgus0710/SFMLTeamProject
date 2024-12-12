#pragma once

#include "UISpriteGameObject.h"

class KeyActionUI;

class ControllerUIBar : public UISpriteGameObject
{
private:
	std::vector<KeyActionUI*> keyActionUIVector;
private:
	void CreateActionKeyUI();

public:
	void SetActive(const bool active) override;
	void Start() override;
public:
	ControllerUIBar(const std::string& texId, const std::string& name = "");
	virtual ~ControllerUIBar() = default;
	ControllerUIBar& operator= (const UISpriteGameObject& other) = delete;

};

