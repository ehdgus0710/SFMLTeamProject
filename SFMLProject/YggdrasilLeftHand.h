#pragma once

#include "AnimationGameObject.h"
#include "YggdrasilFSM.h"
class Rigidbody;
class Player;

class YggdrasilLeftHand : public AnimationGameObject
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

	void SetAniLeftHand(std::string name, bool loop);

	void SetYggdrasil(Yggdrasil* yggdrasil);
	void SetPlayer(Player* player);


	bool GetHeadSkillOn() { return skillOn; }
	void SetHeadSkillOn(bool onoff) { skillOn = onoff; }

	PlayerSaveData GetPlayerSaveData() const;
	void LoadData(const PlayerSaveData& data);
public:
	YggdrasilLeftHand(const std::string& name = "YggdrasilLeftHand");
	virtual ~YggdrasilLeftHand();
	YggdrasilLeftHand& operator= (const YggdrasilLeftHand& other) = delete;
};

