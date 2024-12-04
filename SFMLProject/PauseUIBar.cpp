#include "stdafx.h"
#include "PauseUIBar.h"

PauseUIBar::PauseUIBar(const std::string& texId, const std::string& name)
	: UISpriteGameObject(texId, name)
{
	prevTimeScale = TimeManager::GetInstance().GetTimeScale();
}

void PauseUIBar::SetActive(const bool active)
{
	this->active = active;
	if (active)
	{
		InputManager::GetInstance().SetInputable(false);
		prevTimeScale = TimeManager::GetInstance().GetTimeScale();
		TimeManager::GetInstance().SetTimeScale(0.f);
	}
	else
	{
		InputManager::GetInstance().SetInputable(true);
		TimeManager::GetInstance().SetTimeScale(prevTimeScale);
	}
}
