#pragma once

class Collision
{
protected:
	ColliderType	colliderType;

	sf::Vector2f	position;
	sf::Vector2f	scale;
	sf::Vector2f	originPosition;

	Origins			originsPreset;
	float			rotation;
	
	int collisionCount;

public:
	void IsCollision() { ++collisionCount; }
	void EndCollision() { --collisionCount; }

	virtual void SetScale(const sf::Vector2f& scale);
	virtual sf::Vector2f GetScale() const = 0;

	virtual void SetPosition(const sf::Vector2f& pos) { position = pos; }
	virtual sf::Vector2f GetPosition() { return position; }

	virtual void SetOrigin(const Origins& origins) = 0;
	virtual void SetOrigin(const sf::Vector2f& origins) { originPosition = origins; }
	virtual sf::Vector2f GetOrigin() { return originPosition; }
	Origins GetOrigins() { return originsPreset; }

	virtual void SetRotation(float angle) {}
	virtual float GetRotation() const { return rotation; }

	const ColliderType GetColliderType() { return colliderType; }

	virtual sf::FloatRect GetLocalBounds() = 0;
	virtual sf::FloatRect GetGlobalBounds() = 0;

	virtual sf::Vector2f GetRealPosition() const = 0;
public:
	virtual void Init() = 0;
	virtual void Reset() = 0;
	virtual void Update();
	virtual void Render(sf::RenderWindow& renderWindow);

public:
	Collision(ColliderType colliderType);
	virtual ~Collision() {}

};

