#include "stdafx.h"
#include "EnemySpawnerGUI.h"
#include "imgui.h"
#include "EnemySpawner.h"

EnemySpawnerGUI::EnemySpawnerGUI()
	: ComponentGUI(ComponentGUIType::EnemySpawner)
	, enemySpawner(nullptr)
{
}

EnemySpawnerGUI::~EnemySpawnerGUI()
{
}

void EnemySpawnerGUI::Update()
{
	if (enemySpawner == nullptr)
		return;
	ImGui::Text("EnemySpawner");
	ImGui::BeginChild("##EnemySpawner", { 500.f,500.f });

	static const EnemySpawnerTypeEnum objectEnum[] =
	{
		{ EnemyType::End , "End"}
	};

	int idx;
	for (idx = 0; idx < (int)EnemyType::End; ++idx)
	{
		if (objectEnum[idx].type == currentType)
			break;
	}

	bool isSelect = false;
	if (ImGui::BeginCombo("CreateObjectTypeCombo", objectEnum[idx].name.c_str()))
	{
		for (int n = 0; n < (int)EnemyType::End; n++)
		{
			if (ImGui::Selectable(objectEnum[n].name.c_str(), idx == n))
			{
				currentType = objectEnum[n].type;
				enemySpawner->SetSpawnerType(currentType);
			}
		}

		ImGui::EndCombo();
	}

	if (ImGui::Button("AddPosition"))
	{
		enemySpawner->AddSpawnPosition(sf::Vector2f::zero);
	}

	auto& spawnPositions = enemySpawner->GetSpawnPositions();
	int count = (int)spawnPositions.size();

	for (int i = 0; i < count; ++i)
	{
		float Pos[2] = { spawnPositions[i].x, spawnPositions[i].y};

		ImGui::Text(("SpawnPositions" + std::to_string(i)).c_str()); ImGui::SameLine();
		if (ImGui::InputFloat2(("##SpawnPositions" + std::to_string(i)).c_str(), Pos))
		{
			spawnPositions[i].x = Pos[0];
			spawnPositions[i].y = Pos[1];

			enemySpawner->SetSpawnPosition(spawnPositions[i], i);
		}
	}

	ImGui::EndChild();
}

void EnemySpawnerGUI::SetObject(GameObject * object)
{
	target = object;

	if (target == nullptr)
	{
		enemySpawner = nullptr;
		return;
	}

	enemySpawner = dynamic_cast<EnemySpawner*>(target);
}
