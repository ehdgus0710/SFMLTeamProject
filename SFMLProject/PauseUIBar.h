#pragma once
#include "UISpriteGameObject.h"

class UITextGameObject;
class TextButton;
class MouseObject;
class SettingUIBar;
class BackgroundColorBox;
class ControllerUIBar;

class PauseUIBar : public UISpriteGameObject
{
private:
	SettingUIBar*				settingUIBar;
	UITextGameObject*			pauseText;
	
	TextButton*					goBackButton;
	TextButton*					newGameButton;
	TextButton*					controllerButton;
	TextButton*					settingButton;
	TextButton*					endGameButton;
	MouseObject*				mouseObject;
	BackgroundColorBox*			backgroundRect;
	ControllerUIBar*			controllerUIBar;
	std::vector<TextButton*>	buttons;
	float						prevTimeScale;

private:
	void OffUIBar();
	void OnNewGame();
	void OnControllerBar();
	void OnSettingBar();
	void OffSettingBar();
	void OffControllerBar();
	void OnEndGame();
	void OnPlayUIMoveSound();

	void CreateUIObject();
	void SetChildActive(const bool active);
public:
	void SetActive(const bool active) override;
	void Start() override;
public:
	PauseUIBar(const std::string& texId, const std::string& name = "");
	virtual ~PauseUIBar() = default;
	PauseUIBar& operator= (const UISpriteGameObject& other) = delete;

};

