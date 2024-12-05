#include "stdafx.h"
#include "SoundScrollObject.h"


SoundScrollObject::SoundScrollObject(MoveType moveType, const std::string& textureID, const std::string& name)
	: ScrollButtonUI(moveType, textureID, name)
{
}

SoundScrollObject::SoundScrollObject(MoveType moveType, const sf::Vector2f& startPosition, float minRange, float maxRange, const std::string& textureID, const std::string& name) 
	: ScrollButtonUI(moveType, startPosition, minRange, maxRange, textureID, name)
{
}

void SoundScrollObject::Start()
{
}

void SoundScrollObject::Update(const float& deltaTime)
{
}

void SoundScrollObject::OnCollisionEnter(Collider* target)
{
}

void SoundScrollObject::OnCollisionStay(Collider* target)
{
}

void SoundScrollObject::OnCollisionEnd(Collider* target)
{
}