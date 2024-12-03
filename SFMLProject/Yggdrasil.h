#pragma once
#include "AnimationGameObject.h"
#include "YggdrasilFSM.h"

class YggdrasilMouth;
class YggdrasilHead;
class YggdrasilLeftHand;
class YggdrasilRightHand;
class Player;

class Yggdrasil : public AnimationGameObject
{
protected:
	Player*						player;
	YggdrasilMouth*				yggdrasilMouth;
	YggdrasilHead*				yggdrasilHead;
	YggdrasilLeftHand*			yggdrasilLeftHand;
	YggdrasilRightHand*			yggdrasilRightHand;

	GameObject*					gameObject;

	DefaultStatus				currentStatus;
	sf::Sprite					sprite;
	YggdrasilFSM				fsm;

	int							phase1Hp;
	int							phase2Hp;

	float						attackTime;
	float						attackDelay;

	bool						phaseUp;
public:
	void Awake() override;
	void Start() override;
	void Update(const float& deltaTime) override;
	void FixedUpdate(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;

	sf::Vector2f GetHeadPos();
	sf::Vector2f GetLeftFistPos();
	sf::Vector2f GetRightFistPos();
	
	void TakeDamage(const DamegeInfo& damage);
	void OnDead();

	void SetAnimeLeftHand(std::string name, bool loop);
	void SetAnimeRightHand(std::string name, bool loop);

	void SetHeadPos(sf::Vector2f pos);
	void SetLeftFistPos(sf::Vector2f pos);
	void SetRightFistPos(sf::Vector2f pos);

	void OnCollisionEnter(Collider* target) override;
	void OnCollisionStay(Collider* target) override;
	void OnCollisionEnd(Collider* target) override;

	PlayerSaveData GetPlayerSaveData() const;
	void LoadData(const PlayerSaveData& data);

	YggdrasilMouth* GetYggdrasilMouth() { return yggdrasilMouth; }
	YggdrasilHead* GetYggdrasilHead() { return yggdrasilHead; }
	YggdrasilLeftHand* GetYggdrasilLeftHand() { return yggdrasilLeftHand; }
	YggdrasilRightHand* GetYggdrasilRightHand() { return yggdrasilRightHand; }

	void SetPhaseUp(bool phase) { phaseUp = phase; }
	bool GetPhaseUp() { return phaseUp; }

public:
	Yggdrasil(const std::string& name = "Player");
	virtual ~Yggdrasil();
	Yggdrasil& operator= (const Yggdrasil& other) = delete;
};

