#pragma once

#include "Bullet.h"

class KoopaFireBullet : public Bullet
{
public:
	void Start() override;
	void Update(const float& deltaTime) override;
	void OnCollisionEnter(Collider* target) override;
	void Render(sf::RenderWindow& renderWindow) override;
public:
	bool Save() const override;
	bool Load() override;
	bool SaveCsv(const std::string& filePath) const override;
	bool LoadCsv(const std::string& filePath) override;

public:
	KoopaFireBullet(const std::string& texId = "enemis", const std::string& name = "KoopaFireBullet");
	virtual ~KoopaFireBullet() = default;
	KoopaFireBullet& operator= (const KoopaFireBullet& other) = delete;
};

