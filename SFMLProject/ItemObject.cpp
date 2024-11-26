#include "stdafx.h"
#include "ItemObject.h"
#include "Collider.h"
#include "Player.h"

ItemObject::ItemObject(ItemType type, const std::string& texId, const std::string& name)
	: GameObject(name)
	, itemType(type)
	, textureID(texId)
	, isCreateEvent(false)
	, speed(300.f)
{
	CreateCollider(ColliderType::Rectangle, ColliderLayer::Item);
}

void ItemObject::Start()
{
	SetScale(scale);
	SetPosition(position);
	SetRotation(rotation);

	sprite.setTexture(ResourcesManager<sf::Texture>::GetInstance().Get(textureID), true);
	sprite.setTextureRect(textureUVRect);

	SetOrigin(originPreset);
	collider->Reset();
}

void ItemObject::SetOrigin(Origins preset)
{
	originPreset = preset;
	origin = Utils::SetOrigin(sprite, preset);
	collider->SetOrigin(preset);
}

void ItemObject::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	sprite.setOrigin(origin);
	collider->SetOrigin(newOrigin);
}


void ItemObject::SetUVRect(const sf::IntRect uvRect)
{
	textureUVRect = uvRect;
	sprite.setTextureRect(textureUVRect);
}

void ItemObject::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	sprite.setPosition(position);
	collider->SetPosition(position);
}

void ItemObject::CreateEvenet()
{
	isCreateEvent = true;
	createEndPosition = position;
	createEndPosition.y -= 64.f;
	collider->SetActive(false);
	SoundManger::GetInstance().PlaySfx("OutOfTime");
	
}

void ItemObject::SetScale(const sf::Vector2f& scale)
{
	this->scale = scale;
	sprite.setScale(scale);
	collider->SetScale(scale);
	SetOrigin(originPreset);
}

void ItemObject::SetRotation(float angle)
{
	rotation = angle;
	sprite.setRotation(angle);
	collider->SetRotation(angle);
}

sf::Vector2f ItemObject::GetScale() const
{
	return scale;
}

void ItemObject::Update(const float& deltaTime)
{
	if (isCreateEvent)
	{
		position += sf::Vector2f::up * speed * deltaTime;
		if (position.y <= createEndPosition.y)
		{
			isCreateEvent = false;
			collider->SetActive(true);
			position.y = createEndPosition.y;
		}

		SetPosition(position);
	}
}

void ItemObject::Render(sf::RenderWindow& renderWindow)
{
	renderWindow.draw(sprite);
	collider->Render(renderWindow);
}

void ItemObject::OnCollisionEnter(Collider* target)
{
	if (target->GetColliderLayer() == ColliderLayer::Player)
	{
		Player* player = (Player*)target->GetOwner();
		player->AddItem(itemType);
		SetDestory(true);
	}
}

sf::FloatRect ItemObject::GetLocalBounds() const
{
	return sprite.getLocalBounds();
}

sf::FloatRect ItemObject::GetGlobalBounds() const
{
	return sprite.getGlobalBounds();
}

bool ItemObject::Save() const
{
	return false;
}

bool ItemObject::Load()
{
	return false;
}

bool ItemObject::SaveCsv(const std::string& filePath) const
{
	return false;
}

bool ItemObject::LoadCsv(const std::string& filePath)
{
	return false;
}