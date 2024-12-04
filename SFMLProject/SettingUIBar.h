#pragma once
#include "UISpriteGameObject.h"

class UITextGameObject;
class TextButton;
class MouseObject;

class SettingUIBar : public UISpriteGameObject
{
private:
	UITextGameObject* audioText;

	TextButton* goBackButton;
	TextButton* newGameButton;
	TextButton* controllerButton;
	TextButton* settingButton;
	TextButton* endGameButton;

private:
	void OffUIBar();
	void OnNewGame();
	void OnControllerBar();
	void OnSettingBar();
	void OnEndGame();

	void CreateUIObject();
	void SetChildActive(const bool active);
public:
	void SetActive(const bool active) override;
	void Start() override;
public:
	SettingUIBar(const std::string& texId, const std::string& name = "");
	virtual ~SettingUIBar() = default;
	SettingUIBar& operator= (const SettingUIBar& other) = delete;
};

