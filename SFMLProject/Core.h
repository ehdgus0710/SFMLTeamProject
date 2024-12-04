#pragma once

enum class ColliderType
{
	Point,
	Circle,
	Rectangle
};

enum class KeyState
{
	KeyUp,
	KeyDown,
	KeyPressed,
	KeyNone
};
enum class KeyCode
{
	W = 0,
	A,
	S,
	D,
	Space,
	MouseLeftButton,
	MouseRightButton,
	//MiddleButton,

	end
};

enum class SceneIds
{
	None = -1,
	SceneDev1,
	SceneDev2,
	SceneDev3,
	TitleScene,
	Stage1,
	Stage2,
	Stage3,
	Count,
};

enum class Origins
{
	TopLeft, TopCenter, TopRight,
	MiddleLeft, MiddleCenter, MiddleRight,
	BottomLeft, BottomCenter, BottomRight,
	Custom
};


enum class LayerType
{
	Default,
	BackGround_Back,
	SecondGround,
	TileMap,
	Wall,
	BackGround_Forward,
	Item,
	Block,
	Enemy,
	Boss,
	Player,
	PlayerBullet,
	EnemyBullet,

	Effect,
	PlayerEffect,
	EnemyEffect,

	CleraPoint,

	InGameUI,

	UI,
	End
};

enum class ColliderLayer
{
	Default,
	Wall,
	Scaffolding,
	Item,
	Player,
	Enemy,
	Boss,
	Yggdrasil,
	Reiana,
	PlayerBullet,
	EnemyBullet,
	SavePoint,
	CleraPoint,

	UI,

	End
};

enum class CameraType
{
	Main,
	Effet,
	UI,

	End
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

enum class YggdrasilStateType
{
	Idle,
	FistAttack,
	SweepAttack,
	EnergyBallAttack,
	Dead,

	End
};

enum class ReianaStateType
{
	Idle,
	NomalAttack,
	Dash,
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
	GroundAttack,
	ThreeSword,
	None2,
	DropAttack,
	None3,
	Dead,
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
	End
};