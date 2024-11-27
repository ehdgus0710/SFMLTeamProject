#include "stdafx.h"
#include "Chimera.h"

Chimera::Chimera(const std::string& name)
	:AnimationGameObject(name)
	,fsm(this)
{
}

Chimera::~Chimera()
{
}

void Chimera::Awake()
{
}

void Chimera::Start()
{
}

void Chimera::Update(const float& deltaTime)
{
}

void Chimera::FixedUpdate(const float& deltaTime)
{
}

void Chimera::LateUpdate(const float& deltaTime)
{
}

void Chimera::OnCollisionEnter(Collider* target)
{
}

void Chimera::OnCollisionStay(Collider* target)
{
}

void Chimera::OnCollisionEnd(Collider* target)
{
}
