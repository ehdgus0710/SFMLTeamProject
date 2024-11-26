#pragma once
class PhysicsManager : public Singleton<PhysicsManager>
{
	friend class Singleton<PhysicsManager>;


private:
	sf::Vector2f gravity = { 0.f, 9.8f };
	//float dropSpeed;
public:
	void SetGravity(const sf::Vector2f& gravity) { this->gravity = gravity; }

	sf::Vector2f GetGravity() const { return gravity; }

protected:
	PhysicsManager() = default;
	virtual ~PhysicsManager() = default;
	PhysicsManager(const PhysicsManager&) = delete;
	PhysicsManager& operator=(const PhysicsManager&) = delete;
};

