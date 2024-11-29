#pragma once
#include "AnimationGameObject.h"
#include "PlayerFSM.h"

class Rigidbody;
class Player;
class HitBoxObject;

class Head : public AnimationGameObject
{
protected:
	Player*			player;

	sf::Vector2f	skill1StartPos;
	sf::Vector2f	skillEndPos;

	float			skill1OnTime;
	float			currentTime;

	float			moveDirectionX;
	bool			isThrow;
	bool			onSkill;

public:
	void ThrowHead();
	void EndThrow();
	void SetPlayer(Player* player);

	bool IsThrow() { return isThrow; }
	bool IsOnSkill() { return onSkill; }
public:
	void Awake() override;
	void Start() override;
	void Update(const float& deltaTime) override;
	void FixedUpdate(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;

	void OnCollisionEnter(Collider* target) override;
	void OnCollisionStay(Collider* target) override;
	void OnCollisionEnd(Collider* target) override;

	PlayerSaveData GetPlayerSaveData() const;
	void LoadData(const PlayerSaveData& data);
public:
	Head(const std::string& name = "Head");
	virtual ~Head();
	Head& operator= (const Head& other) = delete;
};

