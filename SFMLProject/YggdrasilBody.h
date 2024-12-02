#pragma once
#include "AnimationGameObject.h"
#include "YggdrasilFSM.h"
class Rigidbody;
class Player;

class YggdrasilBody : public AnimationGameObject
{
protected:
	Player* player;


	float		moveDirectionX;
	bool		skillOn;

public:
	void fire();
	void SetPlayer(Player* player);
	bool GetHeadSkillOn() { return skillOn; }
	void SetHeadSkillOn(bool onoff) { skillOn = onoff; }

	PlayerSaveData GetPlayerSaveData() const;
	void LoadData(const PlayerSaveData& data);
public:
	void Awake() override;
	void Start() override;
	void Update(const float& deltaTime) override;
	void FixedUpdate(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;

	void OnCollisionEnter(Collider* target) override;
	void OnCollisionStay(Collider* target) override;
	void OnCollisionEnd(Collider* target) override;
public:
	YggdrasilBody(const std::string& name = "YggdrasilBody");
	virtual ~YggdrasilBody();
	YggdrasilBody& operator= (const YggdrasilBody& other) = delete;
};

