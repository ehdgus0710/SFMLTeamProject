#include "stdafx.h"
#include "ItemBlockObject.h"
#include "rapidcsv.h"

#include "Collider.h"

#include "Player.h"
#include "Rigidbody.h"
#include "Enemy.h"

#include "CoinObject.h"
#include "MushRoomObject.h"
#include "StarObject.h"
#include "FlowerObject.h"
#include "Scene.h"
#include "Animator.h"

#include "GameManager.h"

ItemBlockObject::ItemBlockObject(ItemType type, const std::string& texId, const std::string& changeTexId, const std::string& name)
	: BlockObject(BlockType::Item, texId, name)
	, itemType(type)
	, itemCount(1)
	, changeTextureUvRect(0, 0, 16, 16)
	, hitMoveDistance(32.f)
	, moveSpeed(500.f)
	, isReturn(false)
	, currentMoveTime(0.f)
	, isHit(false)
{
}

void ItemBlockObject::OnChangetRectUV()
{
	render.setTextureRect(changeTextureUvRect);
}

void ItemBlockObject::OnHitMove()
{
	if (!isHit)
	{
		isHit = true;
		startPosition = position;
		endPosition = position;
		endPosition.y -= hitMoveDistance;
		currentMoveTime = 0.f;
	}

	isReturn = false;
}

void ItemBlockObject::CreateItem()
{
	switch (itemType)
	{
	case ItemType::Coin:
	{
		CoinObject* coin = SceneManager::GetInstance().GetCurrentScene()->AddGameObject(new CoinObject(), LayerType::Default);
		coin->SetPosition(position);
		coin->Awake();
		coin->Start();
		coin->GetAnimator()->ChangeAnimation("coinGet", true);
		coin->CreateEvenet();
		GameManager::GetInstance().HaveCoin();
	}
		break;
	case ItemType::MushRoom:
	{
		MushRoomObject* mush = SceneManager::GetInstance().GetCurrentScene()->AddGameObject(new MushRoomObject(), LayerType::Item);
		mush->SetPosition(position);
		mush->Awake();
		mush->Start();
		mush->CreateEvenet();
	}
		break;
	case ItemType::Flower:
	{
		Player* _player = (Player*)SceneManager::GetInstance().GetCurrentScene()->FindGameObject("Player", LayerType::Player);
		if (_player->GetCurrentHP() == 1)
		{
			MushRoomObject* mush = SceneManager::GetInstance().GetCurrentScene()->AddGameObject(new MushRoomObject(), LayerType::Item);
			mush->SetPosition(position);
			mush->Awake();
			mush->Start();
			mush->CreateEvenet();
		}
		else
		{
			FlowerObject* flower = SceneManager::GetInstance().GetCurrentScene()->AddGameObject(new FlowerObject(), LayerType::Item);
			flower->SetPosition(position);
			flower->Awake();
			flower->Start();
			flower->CreateEvenet();
		}
	}
	break;
	case ItemType::Star:
	{
		StarObject* star = SceneManager::GetInstance().GetCurrentScene()->AddGameObject(new StarObject(), LayerType::Item);
		star->SetPosition(position);
		star->Awake();
		star->Start();
		star->CreateEvenet();
	}
		break;
	case ItemType::End:
		break;
	default:
		break;
	}

	--itemCount;
}

void ItemBlockObject::Update(const float& deltaTime)
{
	if (isHit)
	{
		position.y += moveSpeed * deltaTime * (isReturn ? 1.f : -1.f);

		if (!isReturn)
		{
			if (position.y <= endPosition.y)
			{
				position.y = endPosition.y;
				isReturn = true;
			}
		}
		else
		{
			if (position.y >= startPosition.y)
			{
				position.y = startPosition.y;
				isHit = false;
			}
		}

		SetPosition(position);
	}
}

void ItemBlockObject::OnCollisionEnter(Collider* target)
{
	if (itemCount == 0)
	{
		BlockObject::OnCollisionEnter(target);
		return;
	}


	if (target->GetColliderLayer() == ColliderLayer::Player)
	{
		player = (Player*)target->GetOwner();

		sf::Vector2f targetPosition = target->GetPosition();

		Rectangle rect(collider->GetPosition(), collider->GetScale());
		Rectangle targetRect(targetPosition, target->GetScale());
		float prevPositionY = player->GetRigidbody()->GetPrevDropSpeed();

		if (rect.topPosition > targetRect.bottomPosition - prevPositionY)
		{
			player->GetRigidbody()->SetGround(true);
			player->SetPosition({ targetPosition.x , rect.topPosition - target->GetScale().y * 0.5f });
		}
		else if (rect.bottomPosition < targetRect.topPosition - prevPositionY)
		{
			if (abs(position.x - player->GetPosition().x) < 28.f)
			{
				player->SetPosition({ player->GetPosition().x, rect.bottomPosition + target->GetScale().y * 0.5f });
				player->GetRigidbody()->SetVelocity({ player->GetRigidbody()->GetCurrentVelocity().x , 0.f });

				if (itemCount != 0)
				{
					CreateItem();
					OnHitMove();

					auto targets = collider->GetCollisionTargets();

					for (auto& target : targets)
					{
						if (target->GetColliderLayer() == ColliderLayer::Enemy)
						{
							Enemy* enemy = (Enemy*)target->GetOwner();
							enemy->SetHitDirection(enemy->GetPosition().x < position.x ? sf::Vector2f::left : sf::Vector2f::right);
							enemy->TakeDamage();
						}
					}

				}
				if (itemCount == 0)
					OnChangetRectUV();
			}
		}
	}
	else if (target->GetColliderLayer() == ColliderLayer::Enemy || target->GetColliderLayer() == ColliderLayer::Item)
	{
		GameObject* object = target->GetOwner();

		sf::Vector2f targetPosition = target->GetPosition();

		Rectangle rect(collider->GetPosition(), collider->GetScale());
		Rectangle targetRect(targetPosition, target->GetScale());
		float prevPositionY = object->GetRigidbody()->GetCurrentVelocity().y * TimeManager::GetInstance().GetFixedDeletaTime();

		if (rect.topPosition > targetRect.bottomPosition - prevPositionY)
		{
			object->GetRigidbody()->SetGround(true);
			object->SetPosition({ targetPosition.x , rect.topPosition - target->GetScale().y * 0.5f });
		}
	}
}

void ItemBlockObject::OnCollisionStay(Collider* target)
{
	if (itemCount == 0)
	{
		BlockObject::OnCollisionStay(target);
		return;
	}

	if (target->GetColliderLayer() == ColliderLayer::Player)
	{
		Rigidbody* targetRigidbody = player->GetRigidbody();

		Rectangle rect(collider->GetPosition(), collider->GetScale());
		Rectangle targetRect(target->GetPosition(), target->GetScale());

		sf::Vector2f prevPosition = player->GetRigidbody()->GetCurrentVelocity() * TimeManager::GetInstance().GetFixedDeletaTime();


		if (rect.topPosition == targetRect.bottomPosition)
		{
			if (rect.leftPosition > targetRect.leftPosition && rect.leftPosition < targetRect.rightPosition)
				targetRigidbody->SetVelocity({ 0.f, targetRigidbody->GetCurrentVelocity().y });
			else if (rect.rightPosition < targetRect.rightPosition && rect.rightPosition >(targetRect.leftPosition))
				targetRigidbody->SetVelocity({ 0.f, targetRigidbody->GetCurrentVelocity().y });
		}
		else
		{
			if (rect.bottomPosition > targetRect.topPosition)
			{
				if (rect.leftPosition > targetRect.leftPosition && rect.leftPosition < targetRect.rightPosition)
				{
					player->SetPosition({ rect.leftPosition - target->GetScale().x * 0.5f, player->GetPosition().y });
					targetRigidbody->SetVelocity({ 0.f, targetRigidbody->GetCurrentVelocity().y });
				}
				else if (rect.rightPosition < targetRect.rightPosition && rect.rightPosition >(targetRect.leftPosition))
				{
					player->SetPosition({ rect.rightPosition + target->GetScale().x * 0.5f, player->GetPosition().y });
					targetRigidbody->SetVelocity({ 0.f, targetRigidbody->GetCurrentVelocity().y });
				}
			}
			else
			{
				player->SetPosition({ player->GetPosition().x, rect.bottomPosition + target->GetScale().y * 0.5f });
				player->GetRigidbody()->SetVelocity({ player->GetRigidbody()->GetCurrentVelocity().x , 0.f });
			}
		}

	}
	else if (target->GetColliderLayer() == ColliderLayer::Enemy || target->GetColliderLayer() == ColliderLayer::Item)
	{
		GameObject* object = target->GetOwner();
		Rigidbody* targetRigidbody = target->GetOwner()->GetRigidbody();

		Rectangle rect(collider->GetPosition(), collider->GetScale());
		Rectangle targetRect(target->GetPosition(), target->GetScale());

		if (rect.topPosition == targetRect.bottomPosition)
		{
			if (rect.leftPosition > targetRect.leftPosition && rect.leftPosition < targetRect.rightPosition)
				targetRigidbody->SetVelocity({ 0.f, targetRigidbody->GetCurrentVelocity().y });
			else if (rect.rightPosition < targetRect.rightPosition && rect.rightPosition >(targetRect.leftPosition))
				targetRigidbody->SetVelocity({ 0.f, targetRigidbody->GetCurrentVelocity().y });
		}
		else
		{
			if (rect.bottomPosition > targetRect.topPosition)
			{
				if (rect.leftPosition > targetRect.leftPosition && rect.leftPosition < targetRect.rightPosition)
				{
					object->SetPosition({ rect.leftPosition - target->GetScale().x * 0.5f, object->GetPosition().y });
					targetRigidbody->SetVelocity({ 0.f, targetRigidbody->GetCurrentVelocity().y });
				}
				else if (rect.rightPosition < targetRect.rightPosition && rect.rightPosition >(targetRect.leftPosition))
				{
					object->SetPosition({ rect.rightPosition + target->GetScale().x * 0.5f, object->GetPosition().y });
					targetRigidbody->SetVelocity({ 0.f, targetRigidbody->GetCurrentVelocity().y });
				}
			}
		}
	}
}

void ItemBlockObject::OnCollisionEnd(Collider* target)
{
}

bool ItemBlockObject::Save() const
{
	return false;
}

bool ItemBlockObject::Load()
{
	return false;
}

bool ItemBlockObject::SaveCsv(const std::string& filePath) const
{
	std::ofstream outFile(filePath);

	outFile << "OBJECTNAME, TEXTUREID, BLOCK TPYE, RECTSIZEX,RECTSIZEX, TEXTUREUVRECT LEFT, TEXTUREUVRECT TOP, TEXTUREUVRECT WIDTH, TEXTUREUVRECT HEIGHT" << std::endl;

	outFile << name;
	outFile << "," + textureID;
	outFile << "," + std::to_string((int)blockType);
	outFile << "," + std::to_string(rectSize.x);
	outFile << "," + std::to_string(rectSize.y);

	outFile << "," + std::to_string(textureUVRect.left);
	outFile << "," + std::to_string(textureUVRect.top);
	outFile << "," + std::to_string(textureUVRect.width);
	outFile << "," + std::to_string(textureUVRect.height) << std::endl;

	outFile << "ITEMTYPE, ITEMCOUNT, TEXTUREUVRECT LEFT, TEXTUREUVRECT TOP, TEXTUREUVRECT WIDTH, TEXTUREUVRECT HEIGHT" << std::endl;

	outFile << std::to_string((int)itemType);
	outFile << "," + std::to_string((int)itemCount);
	outFile << "," + std::to_string(changeTextureUvRect.left);
	outFile << "," + std::to_string(changeTextureUvRect.top);
	outFile << "," + std::to_string(changeTextureUvRect.width);
	outFile << "," + std::to_string(changeTextureUvRect.height);
	return true;
}

bool ItemBlockObject::LoadCsv(const std::string& filePath)
{
	rapidcsv::Document doc(filePath);

	name = doc.GetCell<std::string>(0, 0);
	textureID = doc.GetCell<std::string>(1, 0);
	blockType = (BlockType)doc.GetCell<int>(2, 0);
	rectSize.x = doc.GetCell<float>(3, 0);
	rectSize.y = doc.GetCell<float>(4, 0);
	textureUVRect.left = doc.GetCell<int>(5, 0);
	textureUVRect.top = doc.GetCell<int>(6, 0);
	textureUVRect.width = doc.GetCell<int>(7, 0);
	textureUVRect.height = doc.GetCell<int>(8, 0);

	itemType = (ItemType)doc.GetCell<int>(0, 2);
	itemCount = doc.GetCell<int>(1, 2);
	changeTextureUvRect.left = doc.GetCell<int>(2, 2);
	changeTextureUvRect.top = doc.GetCell<int>(3, 2);
	changeTextureUvRect.width = doc.GetCell<int>(4, 2);
	changeTextureUvRect.height = doc.GetCell<int>(5, 2);

	render.setTexture(&ResourcesManager<sf::Texture>::GetInstance().Get(textureID));
	render.setTextureRect(textureUVRect);
	SetScale(scale);
	return true;
}

ItemBlockSaveData ItemBlockObject::GetItemBlockSaveData() const
{
	return ItemBlockSaveData({ GetGameObjectSaveData(), GetBlockSaveDate(), changeTextureUvRect, (int)itemType ,itemCount });
}

void ItemBlockObject::LoadItemBlockSaveData(const ItemBlockSaveData& data)
{
	LoadGameObjectData(data.gameObjectSaveData);
	LoadBlockSaveData(data.blockSaveData);

	changeTextureUvRect = data.changeTextureUvRect;
	itemType = (ItemType)data.itemType;
	itemCount = data.itemCount;
}
