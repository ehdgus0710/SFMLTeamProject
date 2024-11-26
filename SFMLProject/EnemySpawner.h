#pragma once
#include "GameObject.h"

class Player;

class EnemySpawner : public GameObject
{
protected:
	sf::RectangleShape			render;
	std::vector<sf::Vector2f>	spawnPositions;

	EnemyType					spawnerType;

	Player*						player;

	float						spawnActiveDistance;
	float						spawnTime;
	float						currentSpawnTime;

public:

	void SetSpawnerType(EnemyType type) { spawnerType = type; }
	void SpawnEnemy();
	void AddSpawnPosition(const sf::Vector2f& pos);
	void SetSpawnPosition(const sf::Vector2f& pos, int index) { if (index < 0 && spawnPositions.size() <= index) return; spawnPositions[index] = pos; }
	std::vector<sf::Vector2f>& GetSpawnPositions() { return spawnPositions; }

public:
	void SetScale(const sf::Vector2f& scale) override;
	void SetRotation(float angle) override;
	void SetPosition(const sf::Vector2f& pos) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;
public:
	void Start() override;
	void Render(sf::RenderWindow& renderWindow) override;
	void Update(const float& deltaTime) override;

	void OnCollisionEnter(Collider* target) override;

	sf::FloatRect GetLocalBounds() const;
	sf::FloatRect GetGlobalBounds() const;
public:
	EnemySpawnerSaveData GetEnemySpawnerSaveData() const;
	void LoadEnemySpawnerSaveData(const EnemySpawnerSaveData& data);

public:
	EnemySpawner(const std::string& name = "EnemySpawner");
	virtual ~EnemySpawner() = default;
	EnemySpawner& operator= (const EnemySpawner& other) = delete;
};

