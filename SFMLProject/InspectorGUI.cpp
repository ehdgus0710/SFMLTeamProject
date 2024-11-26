#include "stdafx.h"
#include "InspectorGUI.h"

#include "imgui.h"
#include "TileMap.h"
#include "TileMapController.h"
#include "SavePointObject.h"

#include "ComponentGUI.h"
#include "TileMapControllerGUI.h"
#include "TileMapGUI.h"
#include "ColliderGUI.h"
#include "AnimationGUI.h"
#include "SavePointGUI.h"
#include "EnemySpawner.h"
#include "EnemySpawnerGUI.h"


InspectorGUI::InspectorGUI(const std::string& name)
	: GUI(name)
	, targetObject(nullptr)
{
	
}

InspectorGUI::~InspectorGUI()
{
	for (auto& componet : componetGUIvector)
	{
		delete componet;
	}
	componetGUIvector.clear();
}

void InspectorGUI::Init()
{
	componetGUIvector.push_back(new AnimationGUI);
	componetGUIvector.push_back(new ColliderGUI);
	componetGUIvector.push_back(new TileMapGUI);
	componetGUIvector.push_back(new TileMapControllerGUI);
	componetGUIvector.push_back(new SavePointGUI);
	componetGUIvector.push_back(new EnemySpawnerGUI);
}

void InspectorGUI::Update()
{
	if (targetObject == nullptr)
	{
		// SetObject(nullptr);
		return;
	}

	bool b = true;
	ImGui::Begin(GetName().c_str(), &b);

	if (targetObject != nullptr && targetObject->GetDestory())
	{
		targetObject = nullptr;
		ImGui::End();
		return;
	}

	TransformInfo();

	for (auto& componet : componetGUIvector)
	{
		componet->Update();
	}


	ImGui::End();
}

void InspectorGUI::SetObject(GameObject* object)
{ 
	targetObject = object; 

	if (targetObject == nullptr)
		return;

	if (targetObject->GetAnimator() != nullptr)
		componetGUIvector[(int)ComponentGUIType::Animator]->SetObject(targetObject);
	else
		componetGUIvector[(int)ComponentGUIType::Animator]->SetObject(nullptr);

	if (targetObject->GetCollider() != nullptr)
		componetGUIvector[(int)ComponentGUIType::Collider]->SetObject(targetObject);
	else
		componetGUIvector[(int)ComponentGUIType::Collider]->SetObject(nullptr);

	if (dynamic_cast<TileMap*>(targetObject) != nullptr)
		componetGUIvector[(int)ComponentGUIType::TileMap]->SetObject(targetObject);
	else
		componetGUIvector[(int)ComponentGUIType::TileMap]->SetObject(nullptr);

	if (dynamic_cast<TileMapController*>(targetObject) != nullptr)
		componetGUIvector[(int)ComponentGUIType::TileMapController]->SetObject(targetObject);
	else
		componetGUIvector[(int)ComponentGUIType::TileMapController]->SetObject(nullptr);
	if (dynamic_cast<SavePointObject*>(targetObject) != nullptr)
		componetGUIvector[(int)ComponentGUIType::SavePoint]->SetObject(targetObject);
	else
		componetGUIvector[(int)ComponentGUIType::SavePoint]->SetObject(nullptr);

	if (dynamic_cast<EnemySpawner*>(targetObject) != nullptr)
		componetGUIvector[(int)ComponentGUIType::EnemySpawner]->SetObject(targetObject);
	else
		componetGUIvector[(int)ComponentGUIType::EnemySpawner]->SetObject(nullptr);
	
}

void InspectorGUI::TransformInfo()
{
	auto name = GetName().c_str();
	sf::Vector2f position = targetObject->GetPosition();
	float pos[2] = { position.x, position.y };
	sf::Vector2f scale = targetObject->GetScale();
	float scaleArr[2] = { scale.x, scale.y };
	float rotation = targetObject->GetRotation();

	sf::Vector2f origin = targetObject->GetOrigin();
	float originArr[2] = { origin.x, origin.y };

	ImGui::Text("Position"); ImGui::SameLine();
	if (ImGui::InputFloat2("##Position", pos))
	{
		position.x = pos[0];
		position.y = pos[1];
		targetObject->SetPosition(position);
	}
	ImGui::Text("Scale   "); ImGui::SameLine();
	if (ImGui::InputFloat2("##Scale", scaleArr))
	{
		scale.x = scaleArr[0];
		scale.y = scaleArr[1];
		targetObject->SetScale(scale);
	}
	ImGui::Text("Rotation"); ImGui::SameLine();
	if (ImGui::InputFloat("##Rotation", &rotation))
	{
		targetObject->SetRotation(rotation);
	}

	ImGui::Text("Origin"); ImGui::SameLine();

	if (ImGui::InputFloat2("##Origin", originArr))
	{
		origin = { originArr[0], originArr[1] };
		targetObject->SetOrigin(origin);
	}


	int idx;
	for (idx = 0; idx < (int)Origins::Custom; ++idx)
	{
		if (originEnum[idx].origin == (targetObject->GetOrigins()))
			break;
	}

	bool isSelect = false;
	if (ImGui::BeginCombo("CurrentOrigin", originEnum[idx].originID.c_str()))
	{
		for (int n = 0; n < (int)Origins::Custom; n++)
		{
			if (ImGui::Selectable(originEnum[n].originID.c_str(), idx == n))
			{
				targetObject->SetOrigin(originEnum[n].origin);
			}
		}

		ImGui::EndCombo();
	}
}
