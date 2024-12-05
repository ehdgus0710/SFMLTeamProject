#pragma once
#include "UISpriteGameObject.h"

class UITextGameObject;
class ScrollButtonUI;
class TextButton;
class PauseUIBar;

class SettingUIBar : public UISpriteGameObject
{
private:
	UITextGameObject*	audioText;
	UITextGameObject*	totalSoundText;
	UITextGameObject*	bgmSoundText;
	UITextGameObject*	effectSoundText;
	UITextGameObject*	settingText;
	TextButton*			returnButton;

	ScrollButtonUI*		totalSoundScroller;
	ScrollButtonUI*		bgmSoundScroller;
	ScrollButtonUI*		effectSoundScroller;

	sf::Color			defalutColor;
	sf::Color			selectionColor;

	std::vector<GameObject*> objects;
	std::function<void()>	returnButtonClickEvent;
private:
	void CreateUIObject();
	void SetChildActive(const bool active);

	void CreateTotalSoundUI(Scene* currentScene);
	void CreateBGMSoundUI(Scene* currentScene);
	void CreateEffectSoundUI(Scene* currentScene);

private:
	void OnSetTotalSound(float value);
	void OnSetBgmSound(float value);
	void OnSetEffectSound(float value);

	void OnCollisionEnterTotalSoundUI();
	void OnCollisionEnterBGMSoundUI();
	void OnCollisionEnterEffectSoundUI();

	void OnCollisionEndTotalSoundUI();
	void OnCollisionEndBGMSoundUI();
	void OnCollisionEndEffectSoundUI();

public:
	void SetReturnClickEvent(std::function<void()> clickEvent);
public:
	void SetActive(const bool active) override;
	void Start() override;
public:
	SettingUIBar(const std::string& texId, const std::string& name = "");
	virtual ~SettingUIBar() = default;
	SettingUIBar& operator= (const SettingUIBar& other) = delete;
};

