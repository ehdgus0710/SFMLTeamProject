#include "stdafx.h"
#include "TileMapControllerGUI.h"
#include "TileMapController.h"


static int itemCurrentIndex = 0;
TileMapControllerGUI::TileMapControllerGUI()
	: ComponentGUI(ComponentGUIType::TileMapController)
{
}

TileMapControllerGUI::~TileMapControllerGUI()
{
}
void TileMapControllerGUI::Update()
{
	if (tileMapController == nullptr)
		return;

	ImGui::BeginChild("##TileMapController", { 300.f,300.f });
	ImGui::SeparatorText("TileMapController");

	static ImGuiComboFlags flags = 0;
	textureVector.clear();
	auto map = ResourcesManager<sf::Texture>::GetInstance().GetResourcesMap();
	for (auto& iter : map)
	{
		textureVector.push_back(iter.second->GetKey());
	}


	if (ImGui::BeginCombo("##Texture", textureVector[itemCurrentIndex].c_str(), flags))
	{
		for (int n = 0; n < textureVector.size(); ++n)
		{
			const bool is_selected = (itemCurrentIndex == n);
			if (ImGui::Selectable(textureVector[n].c_str(), is_selected))
			{
				itemCurrentIndex = n;
				texture = &ResourcesManager<sf::Texture>::GetInstance().Get(textureVector[n]);
				tileMapController->SetSpriteSheetId(textureVector[n]);
			}

			// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
			if (is_selected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndCombo();
	}

	if (texture != nullptr)
		ImGui::Image(*texture, { 300,300 });

	sf::Vector2f cellSize = tileMapController->GetCellSize();
	float cellSizeArr[2] = { cellSize.x, cellSize.y };

	sf::Vector2u cellCount = tileMapController->GetTileCount();
	int cellCountArr[2] = { (int)cellCount.x, (int)cellCount.y };

	sf::Vector2u textureRectSize = tileMapController->GetTileTextureRectSize();
	int textureRectSizeArr[2] = { (int)textureRectSize.x, (int)textureRectSize.y };

	ImGui::Text("CellSize"); ImGui::SameLine();
	if (ImGui::InputFloat2("##CellSize", cellSizeArr))
	{
		if (cellSizeArr[0] > 0.f && cellSizeArr[1] > 0.f)
		{
			cellSize.x = cellSizeArr[0];
			cellSize.y = cellSizeArr[1];
			tileMapController->SetCellSize(cellSize);
			this->cellSize = cellSize;
		}
	}
	ImGui::Text("CellCount"); ImGui::SameLine();
	if (ImGui::InputInt2("##CellCount", cellCountArr))
	{
		if (cellCountArr[0] > 0 && cellCountArr[1] > 0)
		{
			cellCount.x = cellCountArr[0];
			cellCount.y = cellCountArr[1];
			tileMapController->SetCellCount(cellCount);
		}
	}
	ImGui::Text("TextureRectSize"); ImGui::SameLine();
	if (ImGui::InputInt2("##TextureRectSize", textureRectSizeArr))
	{
		if (textureRectSizeArr[0] > 0 && textureRectSizeArr[1] > 0)
		{
			textureRectSize.x = textureRectSizeArr[0];
			textureRectSize.y = textureRectSizeArr[1];
			tileMapController->SetTileTextrueRectSize(textureRectSize);
		}
	}

	if (ImGui::Button("CreateTileMap", { 100.f, 50.f }))
	{
		tileMapController->AddTileMap(1);
	}
	ImGui::SameLine(); if (ImGui::Button("SaveFile", { 100.f, 50.f }))
	{
		tileMapController->SaveCsv("tileMap/" + tileMapController->GetName() + ".csv");
	}

	ImGui::SameLine(); if (ImGui::Button("LoadFile", { 100.f, 50.f }))
	{
		tileMapController->LoadCsv("tileMap/" + tileMapController->GetName() + ".csv");
	}

	static char cName[100];
	ImGui::Text("SaveName Name");
	if (ImGui::InputText("##SaveName", cName, 100))
	{
		saveName = cName;
		tileMapController->SetName(saveName);
	}

	ImGui::EndChild();
}

void TileMapControllerGUI::SetObject(GameObject* object)
{
	target = object;

	if (target == nullptr || (TileMapController*)target == nullptr)
	{
		tileMapController = nullptr;
		return;
	}

	tileMapController = (TileMapController*)target;

}

