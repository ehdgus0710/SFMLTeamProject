#pragma once
#include "GameObject.h"
class HitBoxObject : public GameObject
{
protected:
	GameObject*							owner;
	ColliderLayer						targetLayer;
	uint64_t							hitLayer;

	std::vector<std::function<void()>>	startHitEvents;
	std::vector<std::function<void()>>	endHitEvents;

	sf::Vector2f						offsetPosition;
	float								damage;
	float								lifeTime;
	float								currentLifeTime;
	bool								useLifeTime;
	bool								isOwnerFollow;
	bool								isAutoDestory;

protected:
	void OwnerFollow();

public:
	void SetOwner(GameObject* owner) { this->owner = owner; }
	void SetDamage(float damage) { this->damage = damage; }
	void UseLifeTime(float lifeTime) { this->lifeTime = lifeTime; useLifeTime = true; }
	void OnAutoDestory() { isAutoDestory = true; }

	void AddStartHitEvent(std::function<void()> hitEvent) { startHitEvents.push_back(hitEvent); }
	void AddEndHitEvent(std::function<void()> hitEvent) { endHitEvents.push_back(hitEvent); }

public:
	void SetScale(const sf::Vector2f& scale) override;
	void SetRotation(float angle) override;
	void SetPosition(const sf::Vector2f& pos) override;
	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	sf::FloatRect GetLocalBounds() const;
	sf::FloatRect GetGlobalBounds() const;
public:
	void Awake() override;
	void Start() override;

	void Release() override;
	void Update(const float& deltaTime) override;

	virtual void OnCollisionEnter(Collider* target);
	virtual void OnCollisionStay(Collider* target);
	virtual void OnCollisionEnd(Collider* target);

public:
	bool SaveCsv(const std::string& filePath) const override;
	bool LoadCsv(const std::string& filePath) override;

public:
	HitBoxObject(GameObject* owner, ColliderLayer thisLayerType, ColliderLayer targetLayer, const std::string& name = "HitBox");
	HitBoxObject(GameObject* owner, ColliderLayer thisLayerType, ColliderLayer targetLayer, bool ownerFollow, const sf::Vector2f& offsetPos = sf::Vector2f::zero, const std::string& name = "HitBox");
	virtual ~HitBoxObject();
};

