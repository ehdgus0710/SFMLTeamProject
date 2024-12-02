#pragma once
#include "AnimationGameObject.h"
#include "YggdrasilFSM.h"

class YggdrasilMouth;
class YggdrasilHead;
class YggdrasilLeftHand;
class YggdrasilRightHand;
class YggdrasilEnergyBallBig;
class Player;

class Yggdrasil : public AnimationGameObject
{
protected:
	Player*					player;
	YggdrasilMouth*			yggdrasilMouth;
	YggdrasilHead*			yggdrasilHead;
	YggdrasilLeftHand*		yggdrasilLeftHand;
	YggdrasilRightHand*		yggdrasilRightHand;
	YggdrasilEnergyBallBig* yggdrasilEnergyBallBig;

	GameObject*				gameObject;

	DefaultStatus	currentStatus;
	sf::Sprite			sprite;
	YggdrasilFSM		fsm;

	float					attackTime;
	float					attackDelay;
public:
	void Awake() override;
	void Start() override;
	void Update(const float& deltaTime) override;
	void FixedUpdate(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;

	sf::Vector2f GetEnergyBallBigPos();
	sf::Vector2f GetHeadPos();
	sf::Vector2f GetLeftFistPos();
	sf::Vector2f GetRightFistPos();
	
	void TakeDamage(float damage);
	void OnDead();

	void SetAnimeLeftHand(std::string name, bool loop);
	void SetAnimeRightHand(std::string name, bool loop);


	void SetEnergyBallBigPos(sf::Vector2f pos);
	void SetHeadPos(sf::Vector2f pos);
	void SetLeftFistPos(sf::Vector2f pos);
	void SetRightFistPos(sf::Vector2f pos);

	void OnCollisionEnter(Collider* target) override;
	void OnCollisionStay(Collider* target) override;
	void OnCollisionEnd(Collider* target) override;

	PlayerSaveData GetPlayerSaveData() const;
	void LoadData(const PlayerSaveData& data);

public:
	Yggdrasil(const std::string& name = "Player");
	virtual ~Yggdrasil();
	Yggdrasil& operator= (const Yggdrasil& other) = delete;
};

