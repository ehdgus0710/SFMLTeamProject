#include "stdafx.h"
#include "ChimeraGroundAttackState.h"

ChimeraGroundAttackState::ChimeraGroundAttackState(ChimeraFSM* fsm)
	: ChimeraBaseState(fsm, ChimeraStateType::GroundAttack)

{
}

ChimeraGroundAttackState::~ChimeraGroundAttackState()
{
}

void ChimeraGroundAttackState::StartMove()
{
	chimera->SetPosition(sf::Vector2f::Lerp(startPosition, endPosition, currentTime / moveTime));
	if (currentTime > moveTime)
	{
		playComplete = true;
		currentTime = 0;
	}

}

void ChimeraGroundAttackState::ReturnMove()
{
	chimera->SetPosition(sf::Vector2f::Lerp(saveStartPos, saveEndPos, currentTime / moveTime));
	if (currentTime > moveTime)
	{
		playComplete = false;
		currentTime = 0;
	}
}

void ChimeraGroundAttackState::Awake()
{
}

void ChimeraGroundAttackState::Start()
{
}

void ChimeraGroundAttackState::Enter()
{
	ChimeraBaseState::Enter();
	moveTime = 2.f;
	currentTime = 0.f;
	playComplete = false;

	startPosition = chimera->GetPosition();
	endPosition = chimera->GetPosition() + sf::Vector2f::right * moveDistance*2.f;

	saveEndPos = startPosition;
	saveStartPos = endPosition;
}

void ChimeraGroundAttackState::Exit()
{
	ChimeraBaseState::Exit();
}

void ChimeraGroundAttackState::Update(float deltaTime)
{
	ChimeraBaseState::Update(deltaTime);
	currentTime += deltaTime;

	if (!playComplete)
	{
		StartMove();
	}
	else
	{
		ReturnMove();
	}
}

void ChimeraGroundAttackState::FixedUpdate(float fixedDeltaTime)
{
	ChimeraBaseState::FixedUpdate(fixedDeltaTime);
}

void ChimeraGroundAttackState::LateUpdate(float deltaTime)
{
	ChimeraBaseState::LateUpdate(deltaTime);
}
