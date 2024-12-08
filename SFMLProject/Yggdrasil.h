#pragma once
#include "AnimationGameObject.h"
#include "YggdrasilFSM.h"

class YggdrasilMouth;
class YggdrasilHead;
class YggdrasilLeftHand;
class YggdrasilRightHand;
class Player;
class YggdrasilUIHub;

class Yggdrasil : public AnimationGameObject
{
protected:
	Player*						player;
	YggdrasilMouth*				yggdrasilMouth;
	YggdrasilHead*				yggdrasilHead;
	YggdrasilLeftHand*			yggdrasilLeftHand;
	YggdrasilRightHand*			yggdrasilRightHand;

	GameObject*					gameObject;
	YggdrasilUIHub*				yggdrasilUIHub;

	DefaultStatus				currentStatus;
	sf::Sprite					sprite;
	YggdrasilFSM				fsm;

	int							phase1Hp;
	int							phase2Hp;

	float						attackTime;
	float						attackDelay;

	bool						phaseUp;

	std::function<void(float, float)> changeHpAction;
public:
	void Awake() override;
	void Start() override;
	void Update(const float& deltaTime) override;
	void FixedUpdate(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;

	sf::Vector2f GetHeadPos();
	sf::Vector2f GetMouthPos();
	sf::Vector2f GetLeftFistPos();
	sf::Vector2f GetRightFistPos();
	
	void TakeDamage(const DamegeInfo& damage);
	void OnDead();

	void SetAnimeBody(std::string name, bool loop);
	void SetAnimeHead(std::string name, bool loop);
	void SetAnimeMouth(std::string name, bool loop);
	void SetAnimeLeftHand(std::string name, bool loop);
	void SetAnimeRightHand(std::string name, bool loop);

	void SetHeadPos(sf::Vector2f pos);
	void SetMouthPos(sf::Vector2f pos);
	void SetLeftFistPos(sf::Vector2f pos);
	void SetRightFistPos(sf::Vector2f pos);

	void SetHeadRota(float rota);
	void SetMouthRota(float rota);
	void SetLeftFistRota(float rota);
	void SetRightFistRota(float rota);

	void OnEndPhaseUp();

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

	void SetChangeHpAction(std::function<void(float, float)> action) { changeHpAction = action; }
public:
	Yggdrasil(const std::string& name = "Player");
	virtual ~Yggdrasil();
	Yggdrasil& operator= (const Yggdrasil& other) = delete;
};

