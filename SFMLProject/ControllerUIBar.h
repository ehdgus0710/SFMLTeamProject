#pragma once

#include "UISpriteGameObject.h"

class ControllerUIBar : public UISpriteGameObject
{
private:
	/*std::unordered_map<>
	TextButton* goBackButton;*/
private:

public:
	void SetActive(const bool active) override;
	void Start() override;
public:
	ControllerUIBar(const std::string& texId, const std::string& name = "");
	virtual ~ControllerUIBar() = default;
	ControllerUIBar& operator= (const UISpriteGameObject& other) = delete;

};

