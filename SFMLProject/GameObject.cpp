#include "stdafx.h"
#include "GameObject.h"
#include "Collider.h"
#include "Animator.h"
#include "Rigidbody.h"

int GameObject::instanceID = 0;

GameObject::GameObject(const std::string& name)
    : name(name)
	, originPreset(Origins::MiddleCenter)
	, collider(nullptr)
	, rotation(0.f)
	, scale(sf::Vector2f::one)
	, position(sf::Vector2f::zero)
	, iD(instanceID++)
	, isDestory(false)
	, animator(nullptr)
	, rigidBody(nullptr)
{
}

GameObject::GameObject(const GameObject& other)
	: name(other.name)
	, position(other.position)
	, rotation(other.rotation)
	, scale(other.scale)
	, origin(other.origin)
	, originPreset(other.originPreset)
	, active(other.active)
	, collider(nullptr)
	, isDestory(false)
	, animator(nullptr)
	, iD(instanceID++)
	, rigidBody(nullptr)
{
	if (other.collider != nullptr)
		collider = new Collider(*other.collider);
}

GameObject::~GameObject()
{
	if (collider != nullptr)
		delete collider;

	if (rigidBody != nullptr)
		delete rigidBody;
}

void GameObject::SetDestory(bool destory)
{
	isDestory = destory;
	if (destory && collider != nullptr)
	{
		collider->OnDestory();
	}
}

void GameObject::OnDestory()
{
	if (isDestory)
		return;

	isDestory = true;

	if (collider != nullptr)
	{
		collider->OnDestory();
	}
}

void GameObject::SetActive(const bool active)
{
	this->active = active;
	if (collider != nullptr)
	{
		collider->SetActive(active);
	}
}

void GameObject::SetScale(const sf::Vector2f& scale)
{
	this->scale = scale;
	if (collider != nullptr)
		collider->SetOwnerScale(scale);
}

void GameObject::SetRotation(float angle)
{
	rotation = angle;
	if (collider != nullptr)
		collider->SetRotation(rotation);
}

void GameObject::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	if (collider != nullptr)
		collider->SetPosition(position);
}

void GameObject::SetOrigin(Origins preset)
{
	originPreset = preset;
	origin = {};
}

void GameObject::Awake()
{
}

void GameObject::Start()
{
	if (collider != nullptr)
		collider->Reset();
}

void GameObject::Release()
{
}

void GameObject::Update(const float& deltaTime)
{
}

void GameObject::FixedUpdate(const float& deltaTime)
{
}

void GameObject::LateUpdate(const float& deltaTime)
{
}

void GameObject::Render(sf::RenderWindow& renderWindow)
{
	if(collider != nullptr)
		collider->Render(renderWindow);
}

bool GameObject::CreateCollider(ColliderType colliderType, ColliderLayer colliderLayer, sf::Vector2f offset, sf::Vector2f size)
{
	if (collider == nullptr)
	{
		collider = new Collider(colliderType, colliderLayer, offset, size);
		collider->SetOwner(this);
		collider->SetPosition(position);
		return true;
	}

	return false;
}

void GameObject::CreateAnimator()
{
	if (animator != nullptr)
		return;
}

bool GameObject::Save() const
{
    return false;
}

bool GameObject::Load()
{
    return false;
}

bool GameObject::SaveCsv(const std::string& filePath) const
{
	return false;
}

bool GameObject::LoadCsv(const std::string& filePath)
{
	return false;
}

GameObjectSaveData GameObject::GetGameObjectSaveData() const
{
	return GameObjectSaveData({ name, position, rotation, scale, origin, (int)originPreset, active, sortingOrder, (int)layerType });
}

void GameObject::LoadGameObjectData(const GameObjectSaveData& data)
{
	name = data.name;
	position = data.position;
	rotation = data.rotation;
	scale = data.scale;
	origin = data.origin;
	originPreset = (Origins)data.originPreset;
	active = data.active;
	sortingOrder = data.sortingOrder;
	layerType = (LayerType)data.layerType;
}
