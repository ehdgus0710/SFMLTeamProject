#include "stdafx.h"
#include "Enemy.h"

#include "Rigidbody.h"
#include "Animator.h"
#include "Collider.h"


Enemy::Enemy(EnemyType type, const std::string& name)
    : AnimationGameObject(name)
    , currentStatus(1, 100.f, 0.f, 0.f)
    , isDead(false)
    , fsm(nullptr)
    , moveDirection(sf::Vector2f::left)
    , currentState(EnemyStateType::Idle)
    , isJumpDead(false)
    , isBulletDead(false)
    , enemyType(type)
{
    rigidBody = new Rigidbody(this);
    rigidBody->SetGround(false);
}

Enemy::~Enemy()
{
}


void Enemy::TakeDamage(float damage)
{
    currentStatus.hp -= damage;

    if(currentStatus.hp <= 0)
        OnDead();
}

void Enemy::OnDead()
{
    if (currentStatus.hp == 0)
        fsm->ChangeState(EnemyStateType::Dead);
}

void Enemy::Start()
{
    AnimationGameObject::Start();

    fsm->Start();
}

void Enemy::Update(const float& deltaTime)
{
    fsm->Update(deltaTime);
    animator->Update(deltaTime);
}

void Enemy::FixedUpdate(const float& deltaTime)
{
    fsm->FixedUpdate(deltaTime);
    rigidBody->FixedUpdate(deltaTime);
}

void Enemy::LateUpdate(const float& deltaTime)
{
    fsm->LateUpdate(deltaTime);
    rigidBody->LateUpdate(deltaTime);
}

EnemySaveData Enemy::GetEnemySaveData() const
{
    return EnemySaveData({ GetGameObjectSaveData(), (int)enemyType });
}

void Enemy::LoadEnemySaveData(const EnemySaveData& data)
{
    LoadGameObjectData(data.gameObjectSaveData);
}
