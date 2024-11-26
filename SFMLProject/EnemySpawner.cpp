#include "stdafx.h"
#include "EnemySpawner.h"
#include "Collider.h"
#include "GameManager.h"
#include "Scene.h"

#include "Goomba.h"
#include "KoopaTroopa.h"
#include "Player.h"

EnemySpawner::EnemySpawner(const std::string& name)
	: GameObject(name)
	, player(nullptr)
	, currentSpawnTime(0.f)
	, spawnActiveDistance(3000.f)
	, spawnTime(10.f)
	, spawnerType(EnemyType::Goomba)
{
	CreateCollider(ColliderType::Rectangle, ColliderLayer::SavePoint);
}

void EnemySpawner::SpawnEnemy()
{
	Scene* currentScene = SceneManager::GetInstance().GetCurrentScene();

	switch (spawnerType)
	{
	case EnemyType::Goomba:
	{
		for (auto& pos : spawnPositions)
		{
			Enemy* enemy = currentScene->AddGameObject(new Goomba(), LayerType::Enemy);
			enemy->SetPosition(pos);
			enemy->Awake();
			enemy->Start();
		}
	}
		break;
	case EnemyType::KoopaTroopa:
		for (auto& pos : spawnPositions)
		{
			Enemy* enemy = currentScene->AddGameObject(new KoopaTroopa(), LayerType::Enemy);
			enemy->SetPosition(pos);
			enemy->Awake();
			enemy->Start();
		}
		break;
	case EnemyType::Koopa:
		break;
	case EnemyType::End:
		break;
	default:
		break;
	}
}

void EnemySpawner::AddSpawnPosition(const sf::Vector2f& pos)
{
	spawnPositions.push_back(pos);
}

void EnemySpawner::SetScale(const sf::Vector2f& scale)
{
	this->scale = scale;
	render.setSize(scale);
	collider->SetOwnerScale(scale);
	SetOrigin(originPreset);
}

void EnemySpawner::SetRotation(float angle)
{
	rotation = angle;
	render.setRotation(angle);
	collider->SetRotation(angle);
}

void EnemySpawner::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	render.setPosition(position);
	collider->SetPosition(position);
}

void EnemySpawner::SetOrigin(Origins preset)
{
	originPreset = preset;
	origin = Utils::SetOrigin(render, preset);
	collider->SetOrigin(preset);
}

void EnemySpawner::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	render.setOrigin(origin);
	collider->SetOrigin(newOrigin);
}

void EnemySpawner::Start()
{
	// position = sf::Vector2f(3280.f, 446.f);
	// restartPosition = sf::Vector2f(3280.f, 446.f);
	// scale = sf::Vector2f(10.f, 5000.f);

	player = (Player*)(SceneManager::GetInstance().GetCurrentScene()->FindGameObject("Player", LayerType::Player));

	SetScale(scale);
	SetPosition(position);
	SetRotation(rotation);
	SetOrigin(originPreset);
	collider->Reset();
}

void EnemySpawner::Render(sf::RenderWindow& renderWindow)
{
	collider->Render(renderWindow);
}

void EnemySpawner::Update(const float& deltaTime)
{
	if (spawnActiveDistance < sf::Vector2f::Distance(player->GetPosition(), position))
		return;

	currentSpawnTime += deltaTime;

	if (currentSpawnTime >= spawnTime)
	{
		currentSpawnTime = 0.f;
		SpawnEnemy();
	}
}

void EnemySpawner::OnCollisionEnter(Collider* target)
{
	if (target->GetColliderLayer() == ColliderLayer::Player)
	{

		SetDestory(true);
	}
}

sf::FloatRect EnemySpawner::GetLocalBounds() const
{
	return render.getLocalBounds();
}

sf::FloatRect EnemySpawner::GetGlobalBounds() const
{
	return render.getGlobalBounds();
}

EnemySpawnerSaveData EnemySpawner::GetEnemySpawnerSaveData() const
{
	return EnemySpawnerSaveData({ GetGameObjectSaveData() });
}

void EnemySpawner::LoadEnemySpawnerSaveData(const EnemySpawnerSaveData& data)
{
	LoadGameObjectData(data.gameObjectSaveData);
}