#pragma once
#include "GameObject.h"
class HitBoxObject : public GameObject
{
protected:
	GameObject*										owner;
	ColliderLayer									targetLayer;
	ColliderLayerMask								targetLayerMask;
	DamegeInfo										damageInfo;

	std::vector<std::function<void(GameObject*)>>	startHitEvents;
	std::vector<std::function<void(GameObject*)>>	endHitEvents;
	std::vector<Collider*>							hitTargets;

	sf::Vector2f									offsetPosition;
	float											lifeTime;
	float											currentLifeTime;
	bool											useLifeTime;
	bool											isOwnerFollow;
	bool											isAutoDestory;

protected:
	void OwnerFollow();

public:
	void SetOwner(GameObject* owner) { this->owner = owner; }
	void SetDamage(const DamegeInfo& damageinfo) { damageInfo = damageinfo; }
	void UseLifeTime(float lifeTime) { this->lifeTime = lifeTime; useLifeTime = true; }
	void OnAutoDestory() { isAutoDestory = true; }

	void AddStartHitEvent(std::function<void(GameObject*)> hitEvent) { startHitEvents.push_back(hitEvent); }
	void AddEndHitEvent(std::function<void(GameObject*)> hitEvent) { endHitEvents.push_back(hitEvent); }

	void ClearHitTarget() { hitTargets.clear(); }

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

	void OnCollisionEnter(Collider* target) override;
	void OnCollisionStay(Collider* target) override;
	void OnCollisionEnd(Collider* target) override;

public:
	bool SaveCsv(const std::string& filePath) const override;
	bool LoadCsv(const std::string& filePath) override;

public:
	HitBoxObject(GameObject* owner, ColliderLayer thisLayerType, ColliderLayer targetLayer, const std::string& name = "HitBox");
	HitBoxObject(GameObject* owner, ColliderLayer thisLayerType, ColliderLayer targetLayer, bool ownerFollow, const sf::Vector2f& offsetPos = sf::Vector2f::zero, const std::string& name = "HitBox");
	HitBoxObject(GameObject* owner, ColliderLayer thisLayerType, ColliderLayerMask targetLayer, const std::string& name = "HitBox");
	HitBoxObject(GameObject* owner, ColliderLayer thisLayerType, ColliderLayerMask targetLayer, bool ownerFollow, const sf::Vector2f& offsetPos = sf::Vector2f::zero, const std::string& name = "HitBox");
	virtual ~HitBoxObject();
};

