#pragma once

#include "UISpriteGameObject.h"

class ReianaUIHub : public UISpriteGameObject
{
public:
	ReianaUIHub(const std::string& texId, const std::string& name = "ReianaUIHub");
	virtual ~ReianaUIHub() = default;
	ReianaUIHub& operator= (const ReianaUIHub& other) = delete;
};

