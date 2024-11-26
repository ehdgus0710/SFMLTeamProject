#include "stdafx.h"
#include "LabberObject.h"
#include "Collider.h"
#include "Koopa.h"
#include "Enemy.h"

LabberObject::LabberObject(const sf::IntRect& textureRect, const std::string& texId, const std::string& name)
	: SpriteGameObject(texId, name)
	, textureRect(textureRect)
{
	scale = sf::Vector2f(4.f, 4.f);
	CreateCollider(ColliderType::Rectangle, ColliderLayer::Default);
}


void LabberObject::Start()
{
	Scene* scene = SceneManager::GetInstance().GetCurrentScene();

	for (int i = 0; i < 26; ++i)
	{
		KooparScaffoldingObject* object = scene->AddGameObject(new KooparScaffoldingObject("tiles", "ScaffoldingObject"), LayerType::BackGround);
		scaffoldingObjects.push_back(object);

		object->SetPosition(position + (sf::Vector2f::left * 64.f * (i + 1)) + sf::Vector2f::down * 64.f);
		object->Start();
	}

	// { 2880.000, 448.000 };
	// { 1664.000 , 128.000}
	sprite.setTextureRect(textureRect);
	sprite.setTexture(ResourcesManager<sf::Texture>::GetInstance().Get(textureId));
	SetScale(scale);
	SetPosition(position);
	SetRotation(rotation);

	SetOrigin(originPreset);
}

void LabberObject::SetScale(const sf::Vector2f& scale)
{
	this->scale = scale;
	sprite.setScale(scale);
	collider->SetScale({ textureRect.width * scale.x, textureRect.height * scale.y });
}

void LabberObject::OnCollisionEnter(Collider* target)
{
	if (target->GetColliderLayer() == ColliderLayer::Player)
	{
		auto& objects = SceneManager::GetInstance().GetCurrentScene()->GetObjectVector(LayerType::Enemy);

		for (auto& object : objects)
		{
			Koopa* koopa = dynamic_cast<Koopa*>(object);
			if (koopa != nullptr)
			{
				koopa->SetScaffoldingObjects(scaffoldingObjects);
				koopa->OnDead();
			}
		}

		OnDestory();
	}
} 
