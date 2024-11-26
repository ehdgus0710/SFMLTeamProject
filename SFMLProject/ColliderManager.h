#pragma once

class Collision;
class Collider;

class ColliderManager : public Singleton<ColliderManager>
{
	friend Singleton<ColliderManager>;
private:
	std::unordered_map<std::string, bool> collisionMap;

	std::vector<Collider*> destoryVector;
	// юс╫ц
	std::vector<std::vector<Collider*>>  colliderVectors;
	std::vector<std::vector<bool>> collisionCheckVector;
	
	bool isCollisionRender;
public:
	void Init();
	void Update();
	void Render(sf::RenderWindow& renderWindow);

	void Clear();

	void DestoryColliderCheck();

	void LayerCollision(int left, int right);
	bool CheckCollision(Collider* left, Collider* right);
	bool CheckOBBCollision(Collider* left, Collider* right);
	void SetCollisionCheck(ColliderLayer left, ColliderLayer right);
	void AddCollider(Collider* newCollision, ColliderLayer right);
	void SetDestoryCollider(Collider* destoryCollider) { destoryVector.push_back(destoryCollider); }

	bool IsPointToPointCollision(Collider* left, Collider* right);
	bool IsRectToRectCollision(Collider* left, Collider* right);
	bool IsCircleToCircleCollision(Collider* left, Collider* right);

	bool IsCircleToRectCollision(Collider* left, Collider* right);
	bool IsPointToRectCollision(Collider* left, Collider* right);
	bool IsCircleToPointCollision(Collider* left, Collider* right);
	bool IsCircleToPointCollision(sf::Vector2f circlePosition, float radian, sf::Vector2f pointPosition);

	void DisableColliderRender() { isCollisionRender = false; }
	void ActiveColliderRender() { isCollisionRender = true; }
protected:
	ColliderManager();
	~ColliderManager() override {};
	ColliderManager(const ColliderManager&) = delete;
	ColliderManager& operator=(const ColliderManager&) = delete;
};

