#pragma once


enum class ActionKeyType
{
	LeftMove,
	RightMove,
	Dash,
	Attack,
	Skill1,
	Skill2,
	Jump,
	ChangeSkul,
	Item,
	Down,
	end
};

// State
enum class PlayerStateType
{
	Idle,
	Run,
	Break,
	Jump,
	Hit,
	Dead,
	Falling,
	Dash,
	Attack,
	JumpAttack,
	Skill1,
	Skill2,
	End
};

enum class SkeletonSpearStateType
{
	Idle,
	Run,
	Break,
	Jump,
	Hit,
	Dead,
	Falling,
	Dash,
	Attack,
	JumpAttack,
	Skill1,
	Skill2,
	End
};


enum class YggdrasilStateType
{
	Idle,
	FistAttack,
	SweepAttack,
	EnergyBallAttack,
	YggdrasilSpecialAttack,
	YggdrasilPhaseUp,
	YggdrasilRecovery,
	Dead,

	End
};

enum class ReianaStateType
{
	Idle,
	NomalAttack,
	Dash,
	BackStap,
	GroundAttack,
	ThreeSword,
	Dimension,
	DropAttack,
	Rising,
	Dead,

	End
};

enum class B_ReianaStateType
{
	Idle,
	Dash,
	None,
	BackStap,
	GroundAttack,
	ThreeSword,
	None2,
	DropAttack,
	None3,
	Dead,

	End
};

enum class AwakeReianaStateType
{
	Idle,
	AwakeDimension,
	Dimension,
	DropAttack,
	GroundAttack,
	DiagonalDrop,
	Dead,
	Awake,

	End
};

enum class EnemyStateType
{
	Idle,
	Scout,
	Chase,
	Hit,
	Move,
	Groggy,
	Attack,
	Dead,
	End
};

enum class ObjectType
{
	Wall,
	Item,
};

enum class ItemType
{
	End
};

enum class EnemyType
{
	Reiana,
	End
};

enum class BossType
{
	Yggdrasil,
	Reiana,
	End
};

enum class SkullType
{
	Littlebone,
	Spear,
	End
};


