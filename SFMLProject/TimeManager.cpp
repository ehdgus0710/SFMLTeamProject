#include "stdafx.h"
#include "Core.h"

TimeManager::TimeManager()
	: deltaTime(0.f)
	, realDeltatime(0.f)
	, fixedDeltaTime(0.02f)
	, frameTarget(144)
	, time(0.f)
	, realTime(0.f)
	, timeScale(1)
	, currentFixedTimestep(0.f)
	, maximumAllowedTimestep(0.1f)
	, currentFrame(0)
	, currentFrameTime(0.f)
{
}


bool TimeManager::IsFixedUpdate()
{
	if (currentFixedTimestep >= fixedDeltaTime)
	{
		currentFixedTimestep -= fixedDeltaTime;
		return true;
	}

	return false;
}

void TimeManager::Init()
{
	ResourcesManager<sf::Font>::GetInstance().Load("KOMIKAP", "fonts/KOMIKAP_.ttf");
	clock.restart();
	frameText.setCharacterSize(30);
	frameText.setPosition({});
	frameText.setFont(ResourcesManager<sf::Font>::GetInstance().Get("KOMIKAP"));

	currentFixedTimestep = 1.f / (float)frameTarget;
	fixedDeltaTime = currentFixedTimestep;
}

void TimeManager::Update()
{
	sfTime = clock.restart();
	realDeltatime = deltaTime = sfTime.asSeconds();
	currentFixedTimestep += realDeltatime;

	if (currentFixedTimestep > maximumAllowedTimestep)
		currentFixedTimestep = maximumAllowedTimestep;

	deltaTime *= timeScale;
	realTime += realDeltatime;
	time += deltaTime;

	FrameCheck();
}

void TimeManager::Render(sf::RenderWindow& renderWindow)
{
	renderWindow.draw(frameText);
}

void TimeManager::FrameCheck()
{
	currentFrameTime += realDeltatime;
	++currentFrame;
	if (currentFrameTime >= 1.f)
	{
		frameText.setString(std::to_string(currentFrame));
		currentFrameTime = 0.f;
		currentFrame = 0;
	}
}