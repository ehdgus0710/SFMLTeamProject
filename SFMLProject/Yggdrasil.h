#pragma once
#include "AnimationGameObject.h"
#include "YggdrasilFSM.h"

class YggdrasilBody;
class YggdrasilHead;
class YggdrasilLeftHand;
class YggdrasilRightHand;
class Player;

class Yggdrasil : public AnimationGameObject
{
protected:
	Player*				player;
	YggdrasilBody*		yggdrasilBody;
	YggdrasilHead*		yggdrasilHead;
	YggdrasilLeftHand*	yggdrasilLeftHand;
	YggdrasilRightHand* yggdrasilRightHand;

	GameObject*			gameObject;

	DefaultStatus	currentStatus;
	sf::Sprite			sprite;
	YggdrasilFSM		fsm;

	float				attackTime;
	float				attackDelay;
public:
	void Awake() override;
	void Start() override;
	void Update(const float& deltaTime) override;
	void FixedUpdate(const float& deltaTime) override;
	void LateUpdate(const float& deltaTime) override;

	sf::Vector2f GetLeftFistPos();
	sf::Vector2f GetRightFistPos();
	
	void TakeDamage(float damage);
	void OnDead();

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

