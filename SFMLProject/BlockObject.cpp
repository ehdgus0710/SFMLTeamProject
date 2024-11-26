#include "stdafx.h"
#include "BlockObject.h"
#include "Collider.h"

#include "Player.h"
#include "Rigidbody.h"

#include "rapidcsv.h"
BlockObject::BlockObject(BlockType type, const std::string& texId, const std::string& name)
    : GameObject(name)
    , blockType(type)
	, textureID(texId)
	, player(nullptr)
	, textureUVRect(0,0,16,16)
	, rectSize(64.f,64.f)
{
	CreateCollider(ColliderType::Rectangle, ColliderLayer::Block);
}

void BlockObject::Start()
{
	SetScale(scale);
	SetPosition(position);
	SetRotation(rotation);
	render.setTexture(&ResourcesManager<sf::Texture>::GetInstance().Get(textureID), true);
	render.setTextureRect(textureUVRect);

	SetOrigin(originPreset);
	collider->Reset();
}

void BlockObject::SetUVRect(const sf::IntRect uvRect)
{
	textureUVRect = uvRect;
	render.setTextureRect(uvRect);
	//rectSize = 
}

void BlockObject::SetScale(const sf::Vector2f& scale)
{
	this->scale = scale;
	render.setSize(rectSize * scale);
	collider->SetOwnerScale(rectSize * scale);
	SetOrigin(originPreset);
}

sf::Vector2f BlockObject::GetScale() const
{
	return scale;
}

void BlockObject::SetSize(const sf::Vector2f& size)
{
	rectSize = size;
	render.setSize(rectSize);
}

void BlockObject::SetRotation(float angle)
{
	rotation = angle;
	render.setRotation(angle);
	collider->SetRotation(angle);
}

void BlockObject::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	render.setPosition(position);
	collider->SetPosition(position);
}

void BlockObject::SetOrigin(Origins preset)
{
	originPreset = preset;
	origin = Utils::SetOrigin(render, preset);
	collider->SetOrigin(preset);
}

void BlockObject::SetOrigin(const sf::Vector2f & newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	render.setOrigin(origin);
	collider->SetOrigin(newOrigin);
}

void BlockObject::OnCollisionEnter(Collider* target)
{
	if (target->GetColliderLayer() == ColliderLayer::Player)
	{
		player = (Player*)target->GetOwner();

		sf::Vector2f targetPosition = target->GetPosition();

		Rectangle rect(collider->GetPosition(), collider->GetScale());
		Rectangle targetRect(targetPosition, target->GetScale());
		float prevPositionY = player->GetRigidbody()->GetCurrentVelocity(). y * TimeManager::GetInstance().GetFixedDeletaTime();

		if (rect.topPosition > targetRect.bottomPosition - prevPositionY)
		{
			player->GetRigidbody()->SetGround(true);
			player->SetPosition({ targetPosition.x , rect.topPosition - target->GetScale().y * 0.5f });
		}
		else if (rect.bottomPosition < targetRect.topPosition - prevPositionY)
		{
			player->SetPosition({ player->GetPosition().x, rect.bottomPosition + target->GetScale().y * 0.5f });
			player->GetRigidbody()->SetVelocity({ player->GetRigidbody()->GetCurrentVelocity().x , 1.f});

			SoundManger::GetInstance().PlaySfx("Bump");
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

void BlockObject::OnCollisionStay(Collider* target)
{
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

void BlockObject::OnCollisionEnd(Collider* target)
{
	/*if (target->GetColliderLayer() == ColliderLayer::Player)
	{
		player = (Player*)target->GetOwner();

		player->GetRigidbody()->SetGround(false);
	}*/
}

sf::FloatRect BlockObject::GetLocalBounds() const
{
	return render.getLocalBounds();
}

sf::FloatRect BlockObject::GetGlobalBounds() const
{
	return render.getGlobalBounds();
}

void BlockObject::Render(sf::RenderWindow& renderWindow)
{
	renderWindow.draw(render);
	collider->Render(renderWindow);
}

bool BlockObject::Save() const
{
    return false;
}

bool BlockObject::Load()
{
    return false;
}

bool BlockObject::SaveCsv(const std::string& filePath) const
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
	outFile << "," + std::to_string(textureUVRect.height);
	return true;
}

bool BlockObject::LoadCsv(const std::string& filePath)
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

	render.setTexture(&ResourcesManager<sf::Texture>::GetInstance().Get(textureID));
	render.setTextureRect(textureUVRect);
	SetScale(scale);
	return true;
}

BlockSaveData BlockObject::GetBlockSaveDate() const
{
	return BlockSaveData({ GetGameObjectSaveData(), (int)blockType, textureUVRect, rectSize, textureID });
}

void BlockObject::LoadBlockSaveData(const BlockSaveData& data)
{
	LoadGameObjectData(data.gameObjectSaveData);
	blockType = (BlockType)data.blockType;
	rectSize = data.rectSize;
	textureUVRect = data.textureUVRect;
	textureID = data.textureID;
}
