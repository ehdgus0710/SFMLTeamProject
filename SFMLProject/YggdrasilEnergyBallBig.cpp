#include "stdafx.h"
#include "YggdrasilEnergyBallBig.h"

#include "Rigidbody.h"
#include "Animator.h"
#include "Collider.h"
#include "Animation.h"

#include "Player.h"

YggdrasilEnergyBallBig::YggdrasilEnergyBallBig(GameObject* owner, ColliderLayer thisLayerType, ColliderLayer targetLayer, const std::string& texId, const std::string& name)
	: AnimationBullet(owner, thisLayerType, targetLayer, texId, name)
	, player(nullptr)
{
	Animation* animation = new Animation("animations/Enemy/yggdrasil/Effects/EnergyBomb.csv");
	animator->AddAnimation(animation, "EnergyBomb");
	animator->ChangeAnimation("EnergyBomb", true);
}


YggdrasilEnergyBallBig::~YggdrasilEnergyBallBig()
{
}


void YggdrasilEnergyBallBig::Awake()
{
	AnimationBullet::Awake();
}

void YggdrasilEnergyBallBig::Start()
{
	AnimationBullet::Start();
}

void YggdrasilEnergyBallBig::Update(const float& deltaTime)
{
	AnimationBullet::Update(deltaTime);
	if (isShoot && player != nullptr)
	{
		SetPosition(position + deltaTime * 100.f * (position.x < player->GetPosition().x ? sf::Vector2f::right : sf::Vector2f::left));
	}
}

void YggdrasilEnergyBallBig::OnCollisionEnter(Collider* target)
{
	if (target->GetColliderLayer() == ColliderLayer::Wall)
	{
		if (position.y < 800.f)
		{
			OnDestory();
			return;
		}

		ResourcesManager<sf::SoundBuffer>::GetInstance().Load("ElderEnt_EnergyBomb_Fire", "AudioClip/Stage1/ElderEnt_EnergyBomb_Fire.wav");
		SoundManger::GetInstance().PlaySfx("ElderEnt_EnergyBomb_Fire");
		lastPos = position;
		OnDestory();
		AnimationGameObject* effect = SceneManager::GetInstance().GetCurrentScene()->AddGameObject(new AnimationGameObject("AttackEffect"), LayerType::Effect);
		Animation* animation(new Animation("animations/Enemy/Yggdrasil/Effects/P2EnergyCorpsExplosion.csv"));
		effect->GetAnimator()->AddAnimation(animation, "P2EnergyCorpsExplosion");
		effect->GetAnimator()->ChangeAnimation("P2EnergyCorpsExplosion");
		animation->SetAnimationEndEvent(std::bind(&GameObject::OnDestory, this), animation->GetEndFrameCount());
		effect->SetPosition({ lastPos.x,lastPos.y +300 });
		effect->SetOrigin(Origins::BottomCenter);
		effect->SetScale({10.f,10.f});

		effect->Awake();
		effect->Start();
	}
	
	else
		AnimationBullet::OnCollisionEnter(target);
}
void YggdrasilEnergyBallBig::SetYggdrasil(Yggdrasil* yggdrasil)
{
}

void YggdrasilEnergyBallBig::SetPlayer(Player* player)
{
	this->player = player;
}

