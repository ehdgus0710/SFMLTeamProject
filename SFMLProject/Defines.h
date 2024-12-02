#pragma once

const static sf::Vector2f& gravity = { 0.f, 9.8f };
#define Gravity gravity

struct DefaultStatus
{
	float		maxHp;
	float		hp;
	float		speed;
	float		attackPower;
	float		magicPower;
	float		attackSpeed;
	float		shield;
	float		defense;
	float		magicDefense;
	float		jumpPower;
	float		maxJumpPower;

	DefaultStatus()
		: maxHp(0.f)
		, hp(0.f)
		, speed(0.f)
		, attackPower(0.f)
		, magicPower(0.f)
		, attackSpeed(0.f)
		, shield(0.f)
		, defense(0.f)
		, magicDefense(0.f)
		, jumpPower(0.f)
		, maxJumpPower(0.f)
	{}
	DefaultStatus(float hp, float speed, float jumpPower, float maxJumpPower)
		: hp(hp), maxHp(hp), speed(speed), jumpPower(jumpPower), maxJumpPower(maxJumpPower) {}

	float GetMaxHp() const { return maxHp; }
	float GetCurrentHp() const { return hp; }
};

struct DefaultStatusSaveData
{
	int			maxHp;
	int			hp;
	float		speed;
	float		jumpPower;
	float		maxJumpPower;

	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(DefaultStatusSaveData, maxHp, hp, speed, jumpPower, maxJumpPower);
};


NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(DefaultStatus, maxHp, hp, speed, jumpPower, maxJumpPower);