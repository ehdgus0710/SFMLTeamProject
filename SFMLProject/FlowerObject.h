#pragma once
#include "ItemObject.h"
class FlowerObject : public ItemObject
{
public:
	void Start() override;
	void Update(const float& deltaTime) override;
	void CreateAnimator() override;
public:
	FlowerObject();
	~FlowerObject() = default;
};

