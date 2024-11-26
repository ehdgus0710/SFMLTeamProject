#include "stdafx.h"
#include "TileMap.h"
#include "rapidcsv.h"

TileMap::TileMap(const std::string& TileId, const std::string& name)
	: GameObject(name)
	, texture(nullptr)
	, spriteSheetId(TileId)
{
}

void TileMap::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	UpdateTransform();
}

void TileMap::SetRotation(float angle)
{
	rotation = angle;
	UpdateTransform();
}

void TileMap::SetScale(const sf::Vector2f& s)
{
	scale = s;
	UpdateTransform();
}
sf::Vector2f TileMap::GetRealScale() const
{
	return realSize;
}
sf::Vector2f TileMap::GetRealPosition() const
{
	return realPosition;
}
void TileMap::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		sf::FloatRect rect = GetLocalBounds();
		origin.x = rect.width * ((int)preset % 3) * 0.5f;
		origin.y = rect.height * ((int)preset / 3) * 0.5f;
		UpdateTransform();
	}
}

void TileMap::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	UpdateTransform();
}

void TileMap::ChangeTextureTile(std::string tileID)
{
	spriteSheetId = tileID;
	this->texture = &TEXTURE_MANAGER.Get(spriteSheetId);
}

void TileMap::SetTileInfo(std::string textId, const sf::Vector2u& cellCount, const sf::Vector2f& tileSize, const sf::Vector2u textureTileSize)
{
	this->cellCount = cellCount;
	cellSize = tileSize;
	this->textureTileSize = textureTileSize;

	vertexArray.clear();
	vertexArray.setPrimitiveType(sf::Quads);
	vertexArray.resize(cellCount.x * cellCount.y * 4);

	this->texture = &TEXTURE_MANAGER.Get(spriteSheetId);

	sf::Vector2f totalTileMapSize = { (sf::Vector2f)cellCount * tileSize };

	sf::Vector2u textureCount = { texture->getSize().x / textureTileSize.x , texture->getSize().y / textureTileSize.y };

	sf::Vector2f positionOffset[4] =
	{
		{ 0.f , 0.f }
		, { tileSize.x , 0.f }
		, { tileSize.x , tileSize.y }
		, { 0.f , tileSize.y }
	};

	sf::Vector2f textUv[4] =
	{
		{ 0.f , 0.f }
		, { (float)textureTileSize.x , 0.f}
		, (sf::Vector2f)textureTileSize
		, {0.f , (float)textureTileSize.y }
	};

	for (int i = 0; i < (int)cellCount.y; ++i)
	{
		sf::Vector2f createPosition = totalTileMapSize * -0.5f;

		for (int j = 0; j < (int)cellCount.x; ++j)
		{
			sf::Vector2i textureIndex = sf::Vector2i::zero;

			auto quadIndex = i * cellCount.x + j;
			sf::Vector2f quadPosition(j * (float)tileSize.y, i * (float)tileSize.y);

			for (int k = 0; k < 4; ++k)
			{
				int vertexIndex = quadIndex * 4 + k;
				vertexArray[vertexIndex].position = quadPosition + positionOffset[k];
				vertexArray[vertexIndex].texCoords = sf::Vector2f::zero;
				vertexArray[vertexIndex].color = sf::Color::Transparent;
				// vertexArray[vertexIndex].texCoords.x += (float)textureIndex.x * (float)textureTileSize.x;
				// vertexArray[vertexIndex].texCoords.y += (float)textureIndex.y * (float)textureTileSize.y;
			}
		}
	}
}

void TileMap::Awake()
{
	/*sortingLayer = SortingLayers::Background;
	sortingOrder = -1;*/

	SetTileInfo(spriteSheetId, { 30,30 }, { 50.f,50.f }, { 50,50 });
	SetOrigin(Origins::MiddleCenter);
}

void TileMap::Release()
{
}

void TileMap::Start()
{
	texture = &TEXTURE_MANAGER.Get(spriteSheetId);

	// position = { 300.055f,300.055f };
	SetScale(sf::Vector2f::one);
	UpdateTransform();

	realSize = cellSize * (sf::Vector2f)cellCount;
	realPosition = position + realSize * 0.5f;
	// SaveCsv("TileMap/test.csv");
}

void TileMap::UpdateTransform()
{
	transform = transform.Identity;
	transform.translate(position);
	transform.rotate(rotation);
	transform.scale(scale);
	transform.translate(-origin);
}

sf::FloatRect TileMap::GetLocalBounds() const
{
	return sf::FloatRect(0.f, 0.f, cellCount.x * cellSize.x, cellCount.y * cellSize.y);
}

sf::FloatRect TileMap::GetGlobalBounds() const
{
	sf::FloatRect bounds = GetLocalBounds();
	return  transform.transformRect(bounds);
}

void TileMap::SetTileCount(const sf::Vector2u& tileCount)
{
	SetTileInfo(spriteSheetId, tileCount, cellSize, textureTileSize);
}

void TileMap::SetCellSize(const sf::Vector2f& cellSize)
{
	SetTileInfo(spriteSheetId, cellCount, cellSize, textureTileSize);
}

void TileMap::SetTileTextrueSize(const sf::Vector2u& texTileSize)
{
}

void TileMap::ChangeTile(int currentIndexX, int currentIndexY, int tileUvPosX, int tileUvPosY)
{
	sf::Vector2f textUv[4] =
	{
		{ 0.f , 0.f }
		, { (float)textureTileSize.x , 0.f}
		, (sf::Vector2f)textureTileSize
		, {0.f , (float)textureTileSize.y }
	};

	int index = (currentIndexY * cellCount.x + currentIndexX) * 4;
	for (int i = 0; i < 4; ++i)
	{
		vertexArray[index + i].texCoords = textUv[i];
		vertexArray[index + i].texCoords.x += textureTileSize.x * tileUvPosX;
		vertexArray[index + i].texCoords.y += textureTileSize.y * tileUvPosY;
		vertexArray[index + i].color = sf::Color::White;
	}
}

void TileMap::Render(sf::RenderWindow& window)
{
	renderState.texture = texture;
	renderState.transform = transform;

	window.draw(vertexArray, renderState);

	if (SceneManager::GetInstance().GetCurrentScene()->IsFreeView())
	{
		sf::RectangleShape outlineRect;
		outlineRect.setFillColor(sf::Color::Transparent);
		outlineRect.setOutlineColor(sf::Color::Green);
		outlineRect.setOutlineThickness(2);
		outlineRect.setSize(GetGlobalBounds().getSize());
		outlineRect.setPosition(GetPosition());
		window.draw(outlineRect);
	}
}

bool TileMap::SaveCsv(const std::string& filePath) const
{
	std::ofstream outFile(filePath);

	outFile << "TEXTUREID,CellCountX,CellCountY,CellSizeX,CellSizeY,TEXTURESIZEX,TEXTURESIZY,PositionX,PositionY,ScaleX,ScaleY,Rotation,ORIGINPRESET" << std::endl;
	outFile << spriteSheetId << "," << cellCount.x << "," << cellCount.y << "," << cellSize.x << "," << cellSize.y << "," << textureTileSize.x << "," << textureTileSize.y;
	outFile << "," << position.x << "," << position.y << "," << scale.x << "," << scale.y << "," << rotation << "," << (int)originPreset << std::endl;


	outFile << std::endl;
	outFile << "CELLTEXCOORDX,CELLTEXCOORDY" << std::endl;

	for (int i = 0; i < (int)cellCount.y; ++i)
	{
		for (int j = 0; j < (int)cellCount.x; ++j)
		{
			int index = (i * cellCount.x + j) * 4;
			for (int k = 0; k < 4; ++k) 
			{
				outFile << vertexArray[index + k].texCoords.x;
				outFile << "," << vertexArray[index + k].texCoords.y;

				outFile << "," << (int)vertexArray[index + k].color.r;
				outFile << "," << (int)vertexArray[index + k].color.g;
				outFile << "," << (int)vertexArray[index + k].color.b;
				outFile << "," << (int)vertexArray[index + k].color.a;
				outFile << std::endl;
			}
		}
	}
	return true;
}

bool TileMap::LoadCsv(const std::string& filePath)
{
	rapidcsv::Document doc(filePath);

	spriteSheetId = doc.GetCell<std::string>(0, 0);
	cellCount.x = doc.GetCell<unsigned int>(1, 0);
	cellCount.y = doc.GetCell<unsigned int>(2, 0);
	cellSize.x = doc.GetCell<float>(3, 0);
	cellSize.y = doc.GetCell<float>(4, 0);
	textureTileSize.x = doc.GetCell<unsigned int>(5, 0);
	textureTileSize.y = doc.GetCell<unsigned int>(6, 0);
	position.x = doc.GetCell<float>(7, 0);
	position.y = doc.GetCell<float>(8, 0);
	scale.x = doc.GetCell<float>(9, 0);
	scale.y = doc.GetCell<float>(10, 0);
	rotation = doc.GetCell<float>(11, 0);
	originPreset = (Origins)doc.GetCell<int>(12, 0);

	vertexArray.clear();
	vertexArray.setPrimitiveType(sf::Quads);
	vertexArray.resize(cellCount.x * cellCount.y * 4);

	texture = &TEXTURE_MANAGER.Get(spriteSheetId);

	sf::Vector2u textureCount = { texture->getSize().x / textureTileSize.x , texture->getSize().y / textureTileSize.y };

	sf::Vector2f positionOffset[4] =
	{
		{ 0.f , 0.f }
		, { cellSize.x , 0.f }
		, { cellSize.x , cellSize.y }
		, { 0.f , cellSize.y }
	};

	sf::Vector2f textUv[4] =
	{
		{ 0.f , 0.f }
		, { (float)textureTileSize.x , 0.f}
		, (sf::Vector2f)textureTileSize
		, {0.f , (float)textureTileSize.y }
	};

	int rowPosition = 3;
	
	for (int i = 0; i < (int)cellCount.y; ++i)
	{
		for (int j = 0; j < (int)cellCount.x; ++j)
		{
			sf::Vector2i textureIndex = sf::Vector2i::zero;

			auto quadIndex = i * cellCount.x + j;
			sf::Vector2f quadPosition(j * (float)cellSize.y, i * (float)cellSize.y);

			for (int k = 0; k < 4; ++k)
			{
				int vertexIndex = quadIndex * 4 + k;
				vertexArray[vertexIndex].position = quadPosition + positionOffset[k];
				vertexArray[vertexIndex].texCoords = { doc.GetCell<float>(0, rowPosition) , doc.GetCell<float>(1 , rowPosition) };
				vertexArray[vertexIndex].color = { (sf::Uint8)doc.GetCell<int>(2, rowPosition),(sf::Uint8)doc.GetCell<int>(3, rowPosition), (sf::Uint8)doc.GetCell<int>(4, rowPosition), (sf::Uint8)doc.GetCell<int>(5, rowPosition) };
				++rowPosition;
			}
		}
	}

	UpdateTransform();
	Start();

	return true;
}
