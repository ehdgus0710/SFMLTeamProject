#pragma once
class Rigidbody : public Entity
{
protected:
	GameObject*		owner;

	sf::Vector2f    accel;
	sf::Vector2f	velocity;
	sf::Vector2f	force;

	float	mass;
	float	dropSpeed;
	float	maxDropSpeed;
	float	prevDropSpeed;
	bool    friction;
	bool	isGround;
	bool	isActive;
public:
	void SetVelocity(const sf::Vector2f& velocity);
 	sf::Vector2f GetCurrentVelocity() const { return velocity; }

	void AddVelocity(const sf::Vector2f& velocity);

	void AddForce(const sf::Vector2f& force);
	sf::Vector2f GetCurrentForce() const { return force; }

	float GetPrevDropSpeed() { return prevDropSpeed; }

	float GetMass() const { return mass; }
	void SetMass(float mass) { this->mass = mass; }

	void SetGround(bool isGround);
	bool IsGround() const { return isGround; }

	void SetMaxDropSpeed(float speed) { maxDropSpeed = speed; }
	float GetMaxDropSpeed() { return maxDropSpeed; }


	void AddDropSpeed(float speed) { dropSpeed += speed; }

	float GetCurrentDropSpeed() { return dropSpeed; }

	void SetOwner(GameObject* owner) { this->owner = owner; }
	GameObject* GetOwner() { return owner; }

	void SetActive(bool active) { isActive = active; }
	void Disable() { isActive = false; }
	bool GetActive() { return isActive; }

	void ResetVelocity();
	void ResetDropSpeed();

public:
	void FixedUpdate(const float& fixedDeltaTime) override;

	void Awake() override;
	void Start() override;

public:
	bool Save() const override;
	bool Load() override;
	bool SaveCsv(const std::string& filePath) const override;
	bool LoadCsv(const std::string& filePath) override;

public:
	Rigidbody(GameObject* owner);
	virtual ~Rigidbody();
};

