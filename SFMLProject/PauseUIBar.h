#pragma once
#include "UISpriteGameObject.h"
class PauseUIBar : public UISpriteGameObject
{
private:
	float prevTimeScale;

public:
	void SetActive(const bool active) override;
public:
	PauseUIBar(const std::string& texId, const std::string& name = "");
	virtual ~PauseUIBar() = default;
	PauseUIBar& operator= (const UISpriteGameObject& other) = delete;

};

