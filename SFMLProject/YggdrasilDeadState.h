#pragma once
#include "YggdrasilBaseState.h"
class Player;
class yggdrasil;

class YggdrasilDeadState : public YggdrasilBaseState
{
protected:
	sf::Vector2f lStartPos;
	sf::Vector2f lEndPos;
	sf::Vector2f rStartPos;
	sf::Vector2f rEndPos;
	sf::Vector2f bStartPos;
	sf::Vector2f bEndPos;
	sf::Vector2f hStartPos;
	sf::Vector2f hEndPos;
	sf::Vector2f mStartPos;
	sf::Vector2f mEndPos;

	float speed;
	float deadTime;
	float deadDelay;
public:
	// void Awake() override;
	// void Start() override;

	void Enter() override;
	void Exit() override;
	void Update(float deltaTime) override;
	void FixedUpdate(float fixedDeltaTime) override;
public:
	YggdrasilDeadState(YggdrasilFSM* fsm);
	~YggdrasilDeadState() = default;
};

