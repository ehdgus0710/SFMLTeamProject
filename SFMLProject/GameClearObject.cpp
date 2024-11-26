#include "stdafx.h"
#include "GameClearObject.h"
#include "Collider.h"
#include "GameManager.h"
#include "Rigidbody.h"
#include "Player.h"
#include "Animator.h"
#include "PlayerFSM.h"
#include "Animation.h"

GameClearObject::GameClearObject(const std::string& name)
	: GameObject(name)
	, player(nullptr)
	, currentTime(0.f)
	, moveTime(1.f)
	, isStartClearEvent(false)
	, currentEventIndex(0)
	, isStartFlip(false)
	, isStartMove(false)
	, endMoveTime(1.5f)
	, currentEndMoveTime(0.f)
	, currentFlagMoveTime(0.f)
	, flagMoveTime(2.f)
{
	CreateCollider(ColliderType::Rectangle, ColliderLayer::CleraPoint);

	gameClearEvents.push_back(std::bind(&GameClearObject::StartMove, this));
	gameClearEvents.push_back(std::bind(&GameClearObject::FlipEvent, this));
	gameClearEvents.push_back(std::bind(&GameClearObject::PlayerCastleMove, this));

	eventCount = (int)gameClearEvents.size();
}

void GameClearObject::SetScale(const sf::Vector2f& scale)
{
	this->scale = scale;
	render.setSize(scale);
	collider->SetOwnerScale(scale);
	SetOrigin(originPreset);
}

void GameClearObject::SetRotation(float angle)
{
	rotation = angle;
	render.setRotation(angle);
	collider->SetRotation(angle);
}

void GameClearObject::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	render.setPosition(position);
	collider->SetPosition(position);
}

void GameClearObject::SetOrigin(Origins preset)
{
	originPreset = preset;
	origin = Utils::SetOrigin(render, preset);
	collider->SetOrigin(preset);
}

void GameClearObject::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	render.setOrigin(origin);
	collider->SetOrigin(newOrigin);
}

void GameClearObject::StartMove()
{
	currentFlagMoveTime += TimeManager::GetInstance().GetUnScaleDeletaTime();
	sf::Vector2f currentPos = player->GetPosition();
	currentPos.y = Utils::Lerp(startPosition.y, destinationPosition.y, currentTime);
	sf::Vector2f currentFlagPos = flagSprite.getPosition();

	currentFlagPos.y = Utils::Lerp(flagStartPosition.y, flagEndPosition.y, currentFlagMoveTime / flagMoveTime);

	if (currentTime >= 1.f)
	{
		startPosition = currentPos;
		player->GetAnimator()->GetCurrentAnimation()->Stop();
		currentTime = 1.f;
		// isStartClearEvent = false;
	}
	if (currentFlagMoveTime >= flagMoveTime)
	{
		++currentEventIndex;		
	}

	flagSprite.setPosition(currentFlagPos);
	player->SetPosition(currentPos);
}

void GameClearObject::FlipEvent()
{
	if (!isStartFlip)
	{
		sf::Vector2f currentPos = player->GetPosition();
		currentPos.x += player->GetCollider()->GetScale().x + 10.f;
		player->SetPosition(currentPos);
		player->OnFlipX();
		isStartFlip = true;
		currentTime = 0.f;
	}
	else
	{
		if (currentTime > 0.5f)
		{
			++currentEventIndex; 
			SoundManger::GetInstance().PlayBgm(("StageClear"), false);
		}
	}
	
}

void GameClearObject::PlayerCastleMove()
{
	if (!isStartMove)
	{
		player->GetRigidbody()->ResetVelocity();
		player->GetRigidbody()->SetActive(true);
		player->GetRigidbody()->SetGround(false);
		player->GetCollider()->SetActive(true);

		if(player->GetCurrentHP() == 1)
			player->GetAnimator()->ChangeAnimation("marioSmallRun", true);
		else if (player->GetCurrentHP() == 2)
			player->GetAnimator()->ChangeAnimation("marioRun", true);
		else if (player->GetCurrentHP() == 3)
			player->GetAnimator()->ChangeAnimation("marioFireRun", true);
		player->OnFlipX();
		isStartMove = true;
		currentEndMoveTime = 0.f;
		startPosition = player->GetPosition();
	}
	else
	{
		sf::Vector2f currentPos = player->GetPosition();
		currentPos.x = Utils::Lerp(startPosition.x, endMovePosition.x, currentEndMoveTime / endMoveTime);
		player->SetPosition(currentPos);

		if (currentEndMoveTime >= endMoveTime)
		{
			GameManager::GetInstance().OnGameClearEvent();
			isStartClearEvent = false;
			player->SetActive(false);
		}
	}
}

void GameClearObject::Start()
{
	flagStartPosition = position + sf::Vector2f(-32.f, -90.f);
	flagEndPosition = flagStartPosition;
	flagEndPosition.y = destinationPosition.y;

	flagSprite.setTexture(ResourcesManager<sf::Texture>::GetInstance().Get("Items"));
	flagSprite.setTextureRect({ 128,32,16,16 });
	flagSprite.setScale(4.f, 4.f);
	flagSprite.setPosition(flagStartPosition);
	Utils::SetOrigin(flagSprite, originPreset);


	SetScale(scale);
	SetPosition(position);
	SetRotation(rotation);
	SetOrigin(originPreset);
	collider->Reset();
}

void GameClearObject::Update(const float& deltaTime)
{
	if (!isStartClearEvent)
		return;

	if (eventCount == currentEventIndex)
		return;

	currentTime += deltaTime;

	if (isStartMove)
		currentEndMoveTime += deltaTime;

	gameClearEvents[currentEventIndex]();
}

void GameClearObject::Render(sf::RenderWindow& renderWindow)
{
	collider->Render(renderWindow);
	renderWindow.draw(flagSprite);
}

void GameClearObject::OnCollisionEnter(Collider* target)
{
	if (target->GetColliderLayer() == ColliderLayer::Player)
	{
		InputManager::GetInstance().SetInputable(true);
		player = (Player*)target->GetOwner();
		player->GetRigidbody()->Disable();

		startPosition = player->GetPosition();
		currentTime = startPosition.y / (destinationPosition.y - maxStartPosition.y);
		isStartClearEvent = true;
		collider->SetActive(false);
		player->GetFSM().ChangeState(PlayerStateType::GameClear);

		GameManager::GetInstance().SetGameClear();
		SoundManger::GetInstance().StopBgm();
		SoundManger::GetInstance().PlaySfx("Flagpole");
		
		//SoundManger::GetInstance().PlayBgm(ResourcesManager<sf::SoundBuffer>::GetInstance().Get("MainTheme"));
	}
}

sf::FloatRect GameClearObject::GetLocalBounds() const
{
	return render.getLocalBounds();
}

sf::FloatRect GameClearObject::GetGlobalBounds() const
{
	return render.getGlobalBounds();
}

GameClearSaveData GameClearObject::GetGameClearSaveData() const
{
	return GameClearSaveData({ GetGameObjectSaveData(), maxStartPosition, destinationPosition, endMovePosition, endMoveTime, moveTime });
}

void GameClearObject::LoadGameClearSaveData(const GameClearSaveData& data)
{
	LoadGameObjectData(data.gameObjectSaveData);
	maxStartPosition = data.maxStartPosition;
	destinationPosition = data.destinationPosition;
	endMovePosition = data.endMovePosition;
	moveTime = data.moveTime;
}
