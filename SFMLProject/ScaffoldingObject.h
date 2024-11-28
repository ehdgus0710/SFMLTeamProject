#pragma once

#include "SpriteGameObject.h"

class ScaffoldingObject : public SpriteGameObject
{

public:
	virtual void OnCollisionEnter(Collider* target);

public:
	ScaffoldingObject(const std::string& texId, const std::string& name = "");
	virtual ~ScaffoldingObject() = default;
	ScaffoldingObject& operator= (const ScaffoldingObject& other) = delete;
};

