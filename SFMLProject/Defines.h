#pragma once

const static sf::Vector2f& gravity = { 0.f, 9.8f };
#define Gravity gravity

struct DefaultStatus
{
	int			maxHp;
	int			hp;
	float		speed;
	float		jumpPower;
	float		maxJumpPower;

	DefaultStatus() {}
	DefaultStatus(int hp, float speed, float jumpPower, float maxJumpPower)
		: hp(hp), maxHp(hp), speed(speed), jumpPower(jumpPower), maxJumpPower(maxJumpPower) {}
};

//struct DefaultStatusSaveData
//{
//	int			maxHp;
//	int			hp;
//	float		speed;
//	float		jumpPower;
//	float		maxJumpPower;
//
//	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(DefaultStatusSaveData, maxHp, hp, speed, jumpPower, maxJumpPower);
//};
//

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(DefaultStatus, maxHp, hp, speed, jumpPower, maxJumpPower);