#pragma once
#include "ItemObject.h"
class CoinObject : public ItemObject
{
private:
	//sf::sprite
	bool isGetCoin;
public:
	void Start() override;
	void Update(const float& deltaTime) override;
	void FixedUpdate(const float& deltaTime) override;
	void CreateAnimator() override;

	void CreateEvenet() override;
public:
	CoinObject();
	~CoinObject() = default;
};