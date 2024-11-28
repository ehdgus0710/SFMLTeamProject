#pragma once
#include "AnimationGameObject.h"
#include "PlayerFSM.h"

class Rigidbody;
class Player;

class Head : public AnimationGameObject
{
protected:
	Player* player;


	float		moveDirectionX;
	bool		skillOn;
public:
	void Awake() override;
	void Start() override;
	void Update(const float& deltaTime) override;
	void FixedUpdate(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;

	void OnCollisionEnter(Collider* target) override;
	void OnCollisionStay(Collider* target) override;
	void OnCollisionEnd(Collider* target) override;

	void fire();

	bool GetHeadSkillOn() { return skillOn; }
	void SetHeadSkillOn(bool onoff) { skillOn = onoff; }

	PlayerSaveData GetPlayerSaveData() const;
	void LoadData(const PlayerSaveData& data);
public:
	Head(const std::string& name = "Head");
	virtual ~Head();
	Head& operator= (const Head& other) = delete;
};

