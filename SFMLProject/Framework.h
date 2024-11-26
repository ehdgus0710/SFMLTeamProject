#pragma once

class Framework
{
private:
	sf::RenderWindow*	renderWindow;
	sf::Event			event;
public:
	void Init();
	void Update();
	void Release();
public:
	Framework();
	~Framework();
};

