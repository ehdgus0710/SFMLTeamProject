#pragma once

#include "GUI.h"

enum class CreateObjectType
{
    Enemy,
    Item,
    SavePoint,
    EnemySpawner,
    End
};

struct CreateObjectTypeEnum
{
    CreateObjectType type;
    std::string name;
};

class CreateObjectTool : public GUI
{
protected:
    std::vector<sf::IntRect>    enemisTextureRects;
    std::vector<sf::IntRect>    blockTextureRects;
    std::vector<sf::IntRect>    itemTextureRects;
    std::vector<std::string>    resoureceVector;
    CreateObjectType            currentType;

    sf::Texture*                texture;
    sf::Sprite                  sprite;

    int                         currentIndex;
    bool                        enemySelect;
    bool                        itemSelect;
    bool                        blockSelect;

    bool                        activeEnemyCreate;
    bool                        activeBlockCreate;
    bool                        activeItemCreate;

public:
    void Init() override;
    void Update() override;

    void OnEnemy();
    void OnItem();
    void OnSavePoint();
    void OnEnemySpawner();
public:
    CreateObjectTool();
    ~CreateObjectTool();
};

