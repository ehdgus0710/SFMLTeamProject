#pragma once

#include "GameObjectSaveData.h"

class Animator;
class Rigidbody;

class GameObject : public Entity
{
protected:
	static int instanceID;

protected:
	sf::Vector2f	position;
	float			rotation;
	sf::Vector2f	scale;
	sf::Vector2f	origin;

	Collider*		collider;
	Animator*		animator;
	Rigidbody*		rigidBody;
	Origins			originPreset;

	LayerType		layerType;

	std::string		name;

	int				iD;
	bool			active = true;
	bool			isDestory;

public:
	int				sortingOrder = 0;

	void SetDestory(bool destory);
	void OnDestory();
	bool GetDestory() { return isDestory; }
	const bool IsActive() const { return active; }
	void SetActive(const bool active) { this->active = active; }
	const std::string& GetName() const { return name; }
	void SetName(const std::string& name) { this->name = name; }

	virtual void SetScale(const sf::Vector2f& scale);
	virtual sf::Vector2f GetScale() const { return scale; }

	virtual void SetRotation(float angle);
	virtual float GetRotation() { return rotation; }

	virtual sf::Vector2f GetPosition() const { return position; }
	virtual void SetPosition(const sf::Vector2f& pos);

	sf::Vector2f GetOrigin() const { return origin; }
	Origins GetOrigins() const { return  originPreset; }
	virtual void SetOrigin(Origins preset);
	virtual void SetOrigin(const sf::Vector2f& newOrigin)
	{
		origin = newOrigin;
		originPreset = Origins::Custom;
	}

	void SetLayerType(const LayerType& layer) { layerType = layer; }
	const LayerType GetLayerType() const { return layerType; }

	virtual sf::FloatRect GetLocalBounds() const = 0;
	virtual sf::FloatRect GetGlobalBounds() const = 0;

	virtual int GetID() { return iD; }

	virtual bool CreateCollider(ColliderType colliderType, ColliderLayer colliderLayer, sf::Vector2f offset = sf::Vector2f::zero, sf::Vector2f size = sf::Vector2f::one);
	virtual void CreateAnimator();

	Collider* GetCollider() { return collider; }
	Animator* GetAnimator() { return animator; }
	Rigidbody* GetRigidbody() { return rigidBody; }
public:
	void Awake() override;
	void Start() override;

	virtual void Release();

	void Update(const float& deltaTime) override;
	void FixedUpdate(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;
	virtual void Render(sf::RenderWindow& renderWindow);

	virtual void OnCollisionEnter(Collider* target) {}
	virtual void OnCollisionStay(Collider* target) {}
	virtual void OnCollisionEnd(Collider* target) {}

public:
	bool Save() const override;
	bool Load() override;
	bool SaveCsv(const std::string& filePath) const override;
	bool LoadCsv(const std::string& filePath) override;

	GameObjectSaveData GetGameObjectSaveData() const;
	void LoadGameObjectData(const GameObjectSaveData& data);

public:
	GameObject(const std::string& name);
	virtual ~GameObject();
	GameObject(const GameObject& other);
	//GameObject& operator=(const GameObject&& other);
};

