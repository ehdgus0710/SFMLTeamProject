#include "stdafx.h"
#include "TileMapGUI.h"
#include "TileMap.h"
#include "Scene.h"

TileMapGUI::TileMapGUI()
	: ComponentGUI(ComponentGUIType::TileMap)
	, tileMap(nullptr)
	, isTileMapEditor(false)
{
}

TileMapGUI::~TileMapGUI()
{
}

void TileMapGUI::Update()
{
	if (tileMap == nullptr)
		return;

	ImGui::BeginChild("##TileMap", { 300.f,300.f });
	ImGui::SeparatorText("TileMap");

	//auto name = GetName().c_str();
	sf::Vector2f cellSize = tileMap->GetCellSize();
	float cellSizeArr[2] = { cellSize.x, cellSize.y };

	sf::Vector2u tileCount = tileMap->GetTileCount();
	int tileCountArr[2] = { (int)tileCount.x, (int)tileCount.y };

	ImGui::Text("CellSize"); ImGui::SameLine();
	if (ImGui::InputFloat2("##CellSize", cellSizeArr))
	{
		if (cellSizeArr[0] > 0.f && cellSizeArr[1] > 0.f)
		{
			cellSize.x = cellSizeArr[0];
			cellSize.y = cellSizeArr[1];
			tileMap->SetCellSize(cellSize);
			this->cellSize = cellSize;
		}
	}
	ImGui::Text("TileCount"); ImGui::SameLine();
	if (ImGui::InputInt2("##TileCount", tileCountArr))
	{
		if (tileCountArr[0] > 0 && tileCountArr[1] > 0)
		{
			tileCount.x = tileCountArr[0];
			tileCount.y = tileCountArr[1];
			tileMap->SetTileCount(tileCount);
		}

	}

	ImVec2 pos = ImGui::GetCursorScreenPos();
	//ImVec2 uv_min = ImVec2(0.0f, 0.0f);                 // Top-left
	//ImVec2 uv_max = ImVec2(1.0f, 1.0f);                 // Lower-right
	//ImVec4 tint_col = use_text_color_for_tint ? ImGui::GetStyleColorVec4(ImGuiCol_Text) : ImVec4(1.0f, 1.0f, 1.0f, 1.0f); // No tint
	//ImVec4 border_col = ImGui::GetStyleColorVec4(ImGuiCol_Border);

	if(texture != nullptr)
		ImGui::Image(*texture, { textureSize.x, textureSize.y });
	OnTileMapEditor();

	ImGui::EndChild();
}

void TileMapGUI::SetObject(GameObject* object)
{
	target = object;
	tileMap = (TileMap*)target;
	if (tileMap == nullptr)
	{
		texture = nullptr;
		return;
	}

	texture = tileMap->GetTexture();
	tileTextureSize = tileMap->GetTileTextrueSize();

	textureSize = sf::Vector2f((float)texture->getSize().x, (float)texture->getSize().y);
	tileUvSize = { 1.f / (textureSize.x / (float)tileTextureSize.x), 1.f / (textureSize.y / (float)tileTextureSize.y) };
	cellSize = tileMap->GetCellSize();
	heightCount = (int)textureSize.y / tileTextureSize.y;
	widthCount = (int)textureSize.x / tileTextureSize.x;
}
void TileMapGUI::OnTileMapEditor()
{
	bool b = ImGui::Button("Edit##MapTool");

	if(!isTileMapEditor)
		isSelect = isTileMapEditor;

	if (b)
	{
		isTileMapEditor = true;
	}
	if (isTileMapEditor)
	{
		ImGui::Begin(tileMap->GetName().c_str(), &isTileMapEditor);

		ImGui::Text("Tile LB = Select , RB = cancel");

		ImVec4			bg_col = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
		ImVec4			tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);

		std::string name = tileMap->GetName();

		if (isSelect)
		{
			if (InputManager::GetInstance().GetKeyPressed(sf::Mouse::Left))
			{
				auto currentPos = SceneManager::GetInstance().GetCurrentScene()->IsFreeView() ? SceneManager::GetInstance().GetCurrentScene()->ScreenToFreeViewWorld(InputManager::GetInstance().GetMousePosition()) : SceneManager::GetInstance().GetCurrentScene()->ScreenToWorld(InputManager::GetInstance().GetMousePosition());
				auto tileMapPos = tileMap->GetGlobalBounds();

				if (tileMapPos.left < currentPos.x && tileMapPos.top < currentPos.y
					&& tileMapPos.left + tileMapPos.width > currentPos.x && tileMapPos.top + tileMapPos.height > currentPos.y)
				{
					int indexX = (int)(currentPos.x - tileMapPos.left) / (int)cellSize.x;
					int indexY = (int)(currentPos.y - tileMapPos.top) / (int)cellSize.y;

					tileMap->ChangeTile(indexX, indexY, selectTileX, selectTileY);
				}
			}
			if (InputManager::GetInstance().GetKeyDown(sf::Mouse::Right))
			{
				isSelect = false;
			}
		}

		for (int i = 0; i < heightCount; ++i)
		{
			for (int j = 0; j < widthCount; ++j)
			{
				ImGui::PushID((i * widthCount) + j);
				ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(1.f, 1.f));

				if (ImGui::ImageButton((name + std::to_string((i * widthCount) + j)).c_str(), texture->getNativeHandle(), { 30.f, 30.f },
					{ tileUvSize.x * j,tileUvSize.y * i}, {tileUvSize.x * (j + 1) ,tileUvSize.y * (i + 1) }, bg_col, tint_col))
				{
					// sf::Vector2f mousePosition = SceneManager::GetInstance().GetCurrentScene()->ScreenToWorld(ImGui::GetMousePos());
					selectTileX = j;
					selectTileY = i;
					isSelect = true;
				}

				if (j != widthCount - 1)
					ImGui::SameLine();

				ImGui::PopStyleVar();
				ImGui::PopID();

			}
		}


		ImGui::End();
	}
}