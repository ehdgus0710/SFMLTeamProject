#include "stdafx.h"
#include "ChimeraGroundAttackState.h"

ChimeraGroundAttackState::ChimeraGroundAttackState(ChimeraFSM* fsm)
	: ChimeraBaseState(fsm, ChimeraStateType::GroundAttack)

{
}

ChimeraGroundAttackState::~ChimeraGroundAttackState()
{
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

	endPosition = chimera->GetPosition() + sf::Vector2f::right * moveDistance;
	startPosition = chimera->GetPosition();
}

void ChimeraGroundAttackState::Exit()
{
	ChimeraBaseState::Exit();
}

void ChimeraGroundAttackState::Update(float deltaTime)
{
	ChimeraBaseState::Update(deltaTime);
	currentTime += deltaTime;
	chimera->SetPosition(sf::Vector2f::Lerp(startPosition, endPosition, currentTime / moveTime));
	if (playComplete && currentTime > moveTime)
	{
		return;
	}
	else if (currentTime > moveTime)
	{
		saveEndPos = startPosition;
		saveStartPos = endPosition;
		startPosition = saveEndPos;
		endPosition = saveStartPos;
		playComplete = true;
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
