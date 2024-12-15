#pragma once

#include "UISpriteGameObject.h"

class KeyActionUI;
class TextButton;

class ControllerUIBar : public UISpriteGameObject
{
private:
	std::vector<KeyActionUI*>	keyActionUIVector;
	TextButton*					resetButton;
	TextButton*					returnButton;

	std::function<void()>	returnButtonClickEvent;
private:
	void CreateActionKeyUI();
	void OnResetKeyAction();

public:

	void SetReturnClickEvent(std::function<void()> clickEvent);

public:
	void SetActive(const bool active) override;
	void Start() override;
public:
	ControllerUIBar(const std::string& texId, const std::string& name = "");
	virtual ~ControllerUIBar() = default;
	ControllerUIBar& operator= (const UISpriteGameObject& other) = delete;

};

