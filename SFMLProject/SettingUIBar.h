#pragma once
#include "UISpriteGameObject.h"

class UITextGameObject;
class ScrollButtonUI;

class SettingUIBar : public UISpriteGameObject
{
private:
	UITextGameObject*	audioText;
	ScrollButtonUI*		totalSoundScroller;
	ScrollButtonUI*		bgmSoundScroller;
	ScrollButtonUI*		effectSoundScroller;
	UITextGameObject*	totalSoundText;
	UITextGameObject*	bgmSoundText;
	UITextGameObject*	effectSoundText;

	std::vector<GameObject*> objects;
private:
	void CreateUIObject();
	void SetChildActive(const bool active);
	void SetTotalSound(float value);
	void SetBgmSound(float value);
	void SetEffectSound(float value);
public:
	void SetActive(const bool active) override;
	void Start() override;
public:
	SettingUIBar(const std::string& texId, const std::string& name = "");
	virtual ~SettingUIBar() = default;
	SettingUIBar& operator= (const SettingUIBar& other) = delete;
};

