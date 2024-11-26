#include "stdafx.h"

WindowManager::~WindowManager()
{
	if (renderWindow != nullptr)
		delete renderWindow;
}

void WindowManager::init(const sf::Vector2u size, const std::string& title)
{
	resolutionSize = size;
	titleName = title;

	sf::VideoMode videoMode(resolutionSize.x, resolutionSize.y);
	renderWindow = new sf::RenderWindow(videoMode, titleName);
#ifdef DEBUG
#else
	renderWindow->setFramerateLimit(300);
#endif 

}
