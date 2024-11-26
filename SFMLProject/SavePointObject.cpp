#include "stdafx.h"
#include "SavePointObject.h"
#include "Collider.h"
#include "GameManager.h"

SavePointObject::SavePointObject(const std::string& name)
	: GameObject(name)
{
	CreateCollider(ColliderType::Rectangle, ColliderLayer::SavePoint);
}

void SavePointObject::SetScale(const sf::Vector2f& scale)
{
	this->scale = scale;
	render.setSize(scale);
	collider->SetOwnerScale(scale);
	SetOrigin(originPreset);
}

void SavePointObject::SetRotation(float angle)
{
	rotation = angle;
	render.setRotation(angle);
	collider->SetRotation(angle);
}

void SavePointObject::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	render.setPosition(position);
	collider->SetPosition(position);
}

void SavePointObject::SetOrigin(Origins preset)
{
	originPreset = preset;
	origin = Utils::SetOrigin(render, preset);
	collider->SetOrigin(preset);
}

void SavePointObject::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	render.setOrigin(origin);
	collider->SetOrigin(newOrigin);
}

void SavePointObject::Start()
{
	/*position = sf::Vector2f(3280.f, 446.f);
	restartPosition = sf::Vector2f(3280.f, 446.f);
	scale = sf::Vector2f(10.f, 5000.f);*/

	SetScale(scale);
	SetPosition(position);
	SetRotation(rotation);
	SetOrigin(originPreset);
	collider->Reset();
}

void SavePointObject::Render(sf::RenderWindow& renderWindow)
{
	collider->Render(renderWindow);
}

void SavePointObject::OnCollisionEnter(Collider* target)
{
	if (target->GetColliderLayer() == ColliderLayer::Player)
	{
		// GameManager::GetInstance().OnSavePoint(restartPosition);
		SetDestory(true);
	}
}

sf::FloatRect SavePointObject::GetLocalBounds() const
{
	return render.getLocalBounds();
}

sf::FloatRect SavePointObject::GetGlobalBounds() const
{
	return render.getGlobalBounds();
}

SavePointSaveData SavePointObject::GetSavePointSaveData() const
{
	return SavePointSaveData({ GetGameObjectSaveData(), restartPosition });
}

void SavePointObject::LoadSavePointSaveData(const SavePointSaveData& data)
{
	LoadGameObjectData(data.gameObjectSaveData);
	restartPosition = data.restartPosition;
}