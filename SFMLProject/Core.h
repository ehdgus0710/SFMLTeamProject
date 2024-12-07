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
	PlayerHead,
	PlayerBullet,
	EnemyBullet,
	SavePoint,
	CleraPoint,
	Door,

	UI,

	End
};

enum class ColliderLayerMask
{
	Default			= 1 << (int)ColliderLayer::Default,
	Wall			= 1 << (int)ColliderLayer::Wall,
	Scaffolding		= 1 << (int)ColliderLayer::Scaffolding,
	Item			= 1 << (int)ColliderLayer::Item,
	Player			= 1 << (int)ColliderLayer::Player,
	Enemy			= 1 << (int)ColliderLayer::Enemy,
	Boss			= 1 << (int)ColliderLayer::Boss,
	Yggdrasil		= 1 << (int)ColliderLayer::Yggdrasil,
	Reiana			= 1 << (int)ColliderLayer::Reiana,
	PlayerHead		= 1 << (int)ColliderLayer::PlayerHead,
	PlayerBullet	= 1 << (int)ColliderLayer::PlayerBullet,
	EnemyBullet		= 1 << (int)ColliderLayer::EnemyBullet,
	SavePoint		= 1 << (int)ColliderLayer::SavePoint,
	CleraPoint		= 1 << (int)ColliderLayer::CleraPoint,
	Door			= 1 << (int)ColliderLayer::Door,
	UI				= 1 << (int)ColliderLayer::UI,

	EnemyAll = Enemy | Boss | Reiana | Yggdrasil,

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
	End
};
