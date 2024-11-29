#pragma once
#include "AnimationGameObject.h"
#include "PlayerFSM.h"

class Rigidbody;
class Player;

class Head : public AnimationGameObject
{
protected:
	Player* player;


	sf::Vector2f	skill1StartPos;
	sf::Vector2f	skillEndPos;

	float			skill1OnTime;
	float			currentTime;

	float			moveDirectionX;
	bool			isThrow;
	bool			skillOn;

public:
	void ThrowHead();
	void SetPlayer(Player* player);

	bool GetHeadSkillOn() { return skillOn; }
	void SetHeadSkillOn(bool onoff) { skillOn = onoff; }
	
	bool IsThrow() { return isThrow; }


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

