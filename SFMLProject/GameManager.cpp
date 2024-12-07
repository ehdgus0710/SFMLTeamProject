#include "stdafx.h"
#include "GameManager.h"
#include "Player.h"
#include "Camera.h"

GameManager::GameManager()
	: isStart(false)
	, isPlaying(false)
	, isRestart(false)
	, isChangeScene(false)
{	  
	playerReStartPosition = sf::Vector2f(1260.f, 777.f);
}


void GameManager::Update(float dt)
{
	
}

void GameManager::Reset()
{
	isStart = false;
	isPlaying = false;
	isRestart = false;
	isChangeScene = false;
}

void GameManager::GameStartInit()
{
}

void GameManager::PlayerDead()
{
	isRestart = true;
}

void GameManager::OnChangeScene()
{
	isChangeScene = true;
}
