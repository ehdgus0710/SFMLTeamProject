#pragma once
#include "Bullet.h"
class KooparHammerBullet : public Bullet
{
private:
	bool isFiring;

public:
	void OnFiring();
	void OnColliderSet90RadionRotation();
	void OnColliderSet0RadionRotation();
public:
	void Start() override;
	void Update(const float& deltaTime) override;
	void FixedUpdate(const float& deltaTime) override;
	void OnCollisionEnter(Collider* target) override;
	void Render(sf::RenderWindow& renderWindow) override;
public:
	KooparHammerBullet(const std::string& texId = "enemis", const std::string& name = "KooparHammerBullet");
	virtual ~KooparHammerBullet() = default;
	KooparHammerBullet& operator= (const KooparHammerBullet& other) = delete;
};

