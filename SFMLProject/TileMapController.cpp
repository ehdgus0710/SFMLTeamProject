#include "stdafx.h"
#include "TileMapController.h"
#include "TileMap.h"
#include "Scene.h"
#include "rapidcsv.h"

TileMapController::TileMapController(const std::string& name)
    : GameObject(name)
    , textureTileSize({16, 16})
    , cellCount(30,20)
    , cellSize(64.f,64.f)
    , spriteSheetId("tiles")
{
}

TileMapController::~TileMapController()
{
}


void TileMapController::SetCellCount(const sf::Vector2u& tileCount)
{
    this->cellCount = tileCount;
}

void TileMapController::SetCellSize(const sf::Vector2f& cellSize)
{
    this->cellSize = cellSize;
}

void TileMapController::SetTileTextrueRectSize(const sf::Vector2u& texTileSize)
{
    textureTileSize = texTileSize;
}

void TileMapController::AddTileMap(int count)
{
    for (int i = 0; i < count; ++i)
    {
        TileMap* tile = SceneManager::GetInstance().GetCurrentScene()->AddGameObject(new TileMap(spriteSheetId, "Map"), LayerType::TileMap);
        if (tileMaps.empty())
        {
            tile->SetPosition(position);
        }
        else
        {
            auto bouns = tileMaps.back()->GetGlobalBounds();
            tile->SetPosition(sf::Vector2f(tileMaps.back()->GetPosition().x + bouns.getSize().x, position.y));
        }
        tile->SetTileInfo(spriteSheetId, cellCount, cellSize, textureTileSize);
        tileMaps.push_back(tile);
    }
}

bool TileMapController::SaveCsv(const std::string& filePath) const
{
    int count = 1;
    std::ofstream outFile(filePath);

    std::vector<std::string> tileMapsSavePaths;

    for (auto& tileMap : tileMaps)
    {
        tileMapsSavePaths.push_back("tileMap/" + name + tileMap->GetName() + std::to_string(count) + ".csv");
        tileMap->SaveCsv("tileMap/" + name + tileMap->GetName() + std::to_string(count++) + ".csv");
    }
    outFile << "TileMapPath" << std::endl;
    outFile << name << std::endl;
    for (auto& tileMapsSavePath : tileMapsSavePaths)
    {
        outFile << tileMapsSavePath << std::endl;
    }

    return true;
}

bool TileMapController::LoadCsv(const std::string& filePath)
{
    rapidcsv::Document doc(filePath);

    name = doc.GetCell<std::string>(0, 0);

    for (int i = 1; i < doc.GetRowCount(); ++i)
    {
        auto row = doc.GetRow<std::string>(i);
        TileMap* tileMap = new TileMap("","TileMap");
        tileMap->LoadCsv(row[0]);
        SceneManager::GetInstance().GetCurrentScene()->AddGameObject(tileMap, LayerType::TileMap);
        tileMaps.push_back(tileMap);
    }

    return true;
}

TileMapSaveData TileMapController::GetTileMapSaveData() const
{
    return TileMapSaveData({ GetGameObjectSaveData(), spriteSheetId, cellCount, cellSize, textureTileSize });
}

void TileMapController::LoadTileMapSaveData(const TileMapSaveData& data)
{
    LoadGameObjectData(data.gameObjectSaveData);
    cellCount = data.cellCount;
    cellSize = data.cellSize;
    spriteSheetId = data.spriteSheetId;
    textureTileSize = data.textureTileSize;

    LoadCsv("tileMap/" + name + ".csv");
}

sf::FloatRect TileMapController::GetLocalBounds() const
{
    return sf::FloatRect();
}

sf::FloatRect TileMapController::GetGlobalBounds() const
{
    return sf::FloatRect();
}
