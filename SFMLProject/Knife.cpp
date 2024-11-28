#include "stdafx.h"
#include "Knife.h"

#include "Collider.h"
#include "Animation.h"
#include "Animator.h"
#include "Enemy.h"
#include "Rigidbody.h"
#include "Player.h"

Knife::Knife(GameObject* owner, ColliderLayer thisLayerType, ColliderLayer targetLayer, const std::string& texId, const std::string& name)
	: AnimationBullet(owner, thisLayerType, targetLayer, texId, name)
{
}

void Knife::Start()
{
	TEXTURE_MANAGER.Load("MenuBar", "graphics/MenuBar_Unselected.png");
	Player* player = dynamic_cast<Player*>(SCENE_MANAGER.GetCurrentScene()->FindGameObject("Player"));

	sprite.setTexture(TEXTURE_MANAGER.Get(textureID));
	moveDirection = player->GetPosition() - position;
	moveDirection.Normalized();

	AnimationBullet::Start();	
} 
void Knife::Update(const float& deltaTime)
{
	if (!isShoot)
	{
		currentDelay += deltaTime;

		SetRotation(Utils::Angle(moveDirection));

		if (currentDelay >= delayTime)
			isShoot = true;
	}

	AnimationBullet::Update(deltaTime);
}