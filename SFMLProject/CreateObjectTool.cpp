#include "stdafx.h"
#include "CreateObjectTool.h"
#include "imgui.h"

#include "Scene.h"
#include "Goomba.h"
#include "BlockObject.h"
#include "ItemBlockObject.h"
#include "BrickBlockObject.h"
#include "GameClearObject.h"
#include "EnemySpawner.h"
#include "KoopaTroopa.h"

#include "SavePointObject.h"

CreateObjectTool::CreateObjectTool()
	: GUI("CreateObjectTool")
	, currentType(CreateObjectType::Enemy)
	, currentIndex(0)
	, texture(nullptr)
{
}

CreateObjectTool::~CreateObjectTool()
{
}

void CreateObjectTool::Init()
{
	enemisTextureRects.push_back({ 0,16,16,16 });
	enemisTextureRects.push_back({96,8,16,32 });

	blockTextureRects.push_back({ 0,0,16,16 });
	blockTextureRects.push_back({ 16,0,16,16 });
	blockTextureRects.push_back({ 32,0,16,16 });
	blockTextureRects.push_back({ 48,0,16,16 });

	blockTextureRects.push_back({ 0,16,16,16 });
	blockTextureRects.push_back({ 16,16,16,16 });
	blockTextureRects.push_back({ 32,16,16,16 });

	blockTextureRects.push_back({ 384,0,16,16 });


	resoureceVector.push_back("enemies");
	resoureceVector.push_back("tiles");
	resoureceVector.push_back("Items");
}

void CreateObjectTool::Update()
{
	ImGui::Begin("CreateObjectTool");

	static const CreateObjectTypeEnum objectEnum[] =
	{
		{ CreateObjectType::Enemy , "Enemy"}
		,{ CreateObjectType::Block , "Block"}
		,{ CreateObjectType::Item , "Item"}
		, { CreateObjectType::SavePoint , "SavePoint"}
		, { CreateObjectType::GameClear , "GameClear"}
		, { CreateObjectType::EnemySpawner , "EnemySpawner"}
	};

	int idx;
	for (idx = 0; idx < (int)CreateObjectType::End; ++idx)
	{
		if (objectEnum[idx].type == currentType)
			break;
	}

	bool isSelect = false;
	if (ImGui::BeginCombo("CreateObjectTypeCombo", objectEnum[idx].name.c_str()))
	{
		for (int n = 0; n < (int)CreateObjectType::End; n++)
		{
			if (ImGui::Selectable(objectEnum[n].name.c_str(), idx == n))
			{
				currentType = objectEnum[n].type;

				if (n < (int)CreateObjectType::SavePoint)
				{
					texture = &ResourcesManager<sf::Texture>::GetInstance().Get(resoureceVector[n]);
					sprite.setTexture(*texture, true);
				}
				

				enemySelect = false;
				itemSelect = false;
				blockSelect = false;
			}
		}

		ImGui::EndCombo();
	}

	if (currentType == CreateObjectType::Enemy)
		OnEnemy();
	else if (currentType == CreateObjectType::Block)
		OnBlock();
	else if (currentType == CreateObjectType::Item)
		OnItem();
	else if (currentType == CreateObjectType::SavePoint)
		OnSavePoint();
	else if (currentType == CreateObjectType::GameClear)
		OnGameClearPoint();
	else if (currentType == CreateObjectType::EnemySpawner)
		OnEnemySpawner();


	ImGui::End();
}

void CreateObjectTool::OnEnemy()
{
	ImGui::BeginChild("Enemy");

	int index = (int)enemisTextureRects.size();

	ImVec4			bg_col = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
	ImVec4			tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);	

	for (int i = 0; i < index; ++i)
	{
		sprite.setTextureRect(enemisTextureRects[i]); 
		ImGui::SameLine();
		if (ImGui::ImageButton(("Enemy" + std::to_string(i)).c_str(), sprite, { 32.f, 32.f }))
		{
			currentIndex = i;
			enemySelect = true;
		}
	}

	ImGui::Text("Select Enemy");
	sprite.setTextureRect(enemisTextureRects[currentIndex]);
	ImGui::Image(sprite, { 32.f, 32.f });

	if (enemySelect)
	{
		if (ImGui::Button("Active Create Enemy", { 50, 20 }))
			activeEnemyCreate = !activeEnemyCreate;

		if (activeEnemyCreate)
		{
			ImGui::Text("Select Enemy");

			if (InputManager::GetInstance().GetKeyUp(sf::Mouse::Left))
			{
				Scene* currentScene = SceneManager::GetInstance().GetCurrentScene();
				Enemy* enemy = nullptr;
				if (currentIndex == 0)
				{
					enemy = currentScene->AddGameObject(new Goomba, LayerType::Enemy);
					enemy->Awake();
					enemy->Start();
				}
				else if (currentIndex == 1)
				{
					enemy = currentScene->AddGameObject(new KoopaTroopa, LayerType::Enemy);
					enemy->Awake();
					enemy->Start();
				}

				if (enemy != nullptr)
				{
					if (currentScene->IsFreeView())
						enemy->SetPosition(currentScene->ScreenToFreeViewWorld(InputManager::GetInstance().GetMousePosition()));
					else
						enemy->SetPosition(currentScene->ScreenToWorld(InputManager::GetInstance().GetMousePosition()));
				}
			}
			
			if (InputManager::GetInstance().GetKeyUp(sf::Mouse::Right))
			{
				activeEnemyCreate = false;
			}
		}
	}

	ImGui::EndChild();
}

void CreateObjectTool::OnBlock()
{
	ImGui::BeginChild("Block");
	int index = (int)blockTextureRects.size();

	ImVec4			bg_col = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
	ImVec4			tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);

	for (int i = 0; i < index; ++i)
	{
		sprite.setTextureRect(blockTextureRects[i]);
		ImGui::SameLine();
		if (ImGui::ImageButton(("Block" + std::to_string(i)).c_str(), sprite, { 32.f, 32.f }))
		{
			currentIndex = i;
			blockSelect = true;
		}
	}

	ImGui::Text("Select Block");
	sprite.setTextureRect(blockTextureRects[currentIndex]);
	ImGui::Image(sprite, { 32.f, 32.f });

	if (blockSelect)
	{
		if (activeBlockCreate)
		{
			ImGui::Text("Select Block");

			if (InputManager::GetInstance().GetKeyUp(sf::Mouse::Left))
			{
				Scene* currentScene = SceneManager::GetInstance().GetCurrentScene();
				BlockObject* block = nullptr;
				if (currentIndex == 1 || currentIndex == 2)
				{
					block = currentScene->AddGameObject(new BrickBlockObject(resoureceVector[1]), LayerType::Block);
				}
				else if (currentIndex == 7)
				{
					block = currentScene->AddGameObject(new ItemBlockObject(ItemType::Coin, resoureceVector[1], resoureceVector[1]), LayerType::Block);
				}
				else
					block = currentScene->AddGameObject(new BlockObject(BlockType::Default, resoureceVector[1]), LayerType::Block);

				if (block != nullptr)
				{
					sf::Vector2f pos;

					if (currentScene->IsFreeView())
						pos = currentScene->ScreenToFreeViewWorld(InputManager::GetInstance().GetMousePosition());
					else
						pos = currentScene->ScreenToWorld(InputManager::GetInstance().GetMousePosition());

					int posX = (int)(pos.x / block->GetRectSize().x) + 1;
					int posY = (int)(pos.y / block->GetRectSize().y) + 1;

					pos = { block->GetRectSize().x * (posX), block->GetRectSize().y * (posY) };
					pos -= (block->GetRectSize() * 0.5f);
					block->SetPosition(pos);

					block->SetUVRect(blockTextureRects[currentIndex]);
					block->Awake();
					block->Start();
				}
			}
		}

		if (ImGui::Button("Active Create Block", { 50, 20 }))
			activeBlockCreate = !activeBlockCreate;

		if (InputManager::GetInstance().GetKeyUp(sf::Mouse::Right))
		{
			activeBlockCreate = false;
		}
	}
	ImGui::EndChild();
}

void CreateObjectTool::OnItem()
{
	ImGui::BeginChild("Item");

	ImGui::EndChild();
}

void CreateObjectTool::OnSavePoint()
{
	ImGui::BeginChild("SavePoint");

	if (ImGui::Button("Create SavePoint", { 50, 20 }))
	{
		SavePointObject* savePointObject = SceneManager::GetInstance().GetCurrentScene()->AddGameObject(new SavePointObject(), LayerType::Default);
	}
	ImGui::EndChild();
}

void CreateObjectTool::OnGameClearPoint()
{
	ImGui::BeginChild("ClearObject");

	if (ImGui::Button("Create ClearObject", { 50, 20 }))
	{
		GameClearObject* gameClearObject = SceneManager::GetInstance().GetCurrentScene()->AddGameObject(new GameClearObject(), LayerType::CleraPoint);
	}
	ImGui::EndChild();
}

void CreateObjectTool::OnEnemySpawner()
{
	ImGui::BeginChild("EnemySpawner");

	if (ImGui::Button("Create EnemySpawner", { 50, 20 }))
	{
		EnemySpawner* enemySpawner = SceneManager::GetInstance().GetCurrentScene()->AddGameObject(new EnemySpawner(), LayerType::Default);
		enemySpawner->Start();
	}
	ImGui::EndChild();
}
