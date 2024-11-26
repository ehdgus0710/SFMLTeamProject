#pragma once

#include "GUI.h"

enum class CollisonObjectType
{
    Wall,
    Trick,

    End
};

struct CollisonObjectTypeEnum
{
    CollisonObjectType type;
    std::string name;
};

class CollisionObjectEditor : public GUI
{
protected:
    sf::Vector2f	cellSize;
    sf::Vector2f    startPosition;
    sf::Vector2f    endPosition;
    CollisonObjectType  currentType;

    bool            isCreateObject;
    bool            isStartInput;
    bool            isEndInput;

public:
    void Init() override;
    void Update() override;

public:
    CollisionObjectEditor();
    ~CollisionObjectEditor();
};

