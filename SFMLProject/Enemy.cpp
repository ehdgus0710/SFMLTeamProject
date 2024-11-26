#include "stdafx.h"
#include "Enemy.h"

#include "Rigidbody.h"
#include "Animator.h"
#include "Collider.h"


Enemy::Enemy(EnemyType type, const std::string& name)
    : GameObject(name)
    , currentStatus(1, 100.f, 0.f, 0.f)
    , isDead(false)
    , isFlipX(false)
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


void Enemy::TakeDamage()
{
    --currentStatus.hp;

    if(currentStatus.hp <= 0)
        OnDead();
    
}

void Enemy::OnDead()
{
    if (currentStatus.hp == 0)
        fsm->ChangeState(EnemyStateType::Dead);
    /*SetDestory(true);
    * 
    if (currentStatus.hp == 0)
        fsm->ChangeState(EnemyStateType::Dead);*/
}

void Enemy::OnFlipX()
{
    isFlipX = !isFlipX;

    scale.x *= -1.f;
    SetScale(scale);
}

void Enemy::SetPosition(const sf::Vector2f& pos)
{
    position = pos;
    sprite.setPosition(pos);
    collider->SetPosition(pos);
}

void Enemy::SetScale(const sf::Vector2f& scale)
{
    this->scale = scale;
    animator->SetScale(scale);
    collider->SetOwnerScale(scale);
}

void Enemy::SetRotation(float angle)
{
    rotation = angle;
    sprite.setRotation(angle);
    collider->SetRotation(angle);
}

void Enemy::SetOrigin(Origins preset)
{
    originPreset = preset;
    origin = Utils::SetOrigin(sprite, preset);
    collider->SetOrigin(preset);
}

void Enemy::SetOrigin(const sf::Vector2f& newOrigin)
{
    originPreset = Origins::Custom;
    origin = newOrigin;
    sprite.setOrigin(origin);
    collider->SetOrigin(newOrigin);
}

void Enemy::CreateAnimator()
{
    if (animator != nullptr)
        return;

    animator = new Animator(this, sprite);
}

void Enemy::Awake()
{
}

void Enemy::Start()
{
    SetScale(scale);
    SetPosition(position);
    SetRotation(rotation);

    SetOrigin(originPreset);
    animator->Start();
    collider->Reset();

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

void Enemy::Render(sf::RenderWindow& renderWindow)
{
    animator->Render(renderWindow);
    collider->Render(renderWindow);
}

sf::FloatRect Enemy::GetLocalBounds() const
{
    return sprite.getLocalBounds();
}

sf::FloatRect Enemy::GetGlobalBounds() const
{
    return sprite.getGlobalBounds();
}

EnemySaveData Enemy::GetEnemySaveData() const
{
    return EnemySaveData({ GetGameObjectSaveData(), (int)enemyType });
}

void Enemy::LoadEnemySaveData(const EnemySaveData& data)
{
    LoadGameObjectData(data.gameObjectSaveData);
}
