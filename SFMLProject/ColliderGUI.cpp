#include "stdafx.h"
#include "ColliderGUI.h"
#include "Collider.h"
#include "imgui.h"


ColliderGUI::ColliderGUI()
	: ComponentGUI(ComponentGUIType::Collider)
	, collider(nullptr)
{
}

ColliderGUI::~ColliderGUI()
{
}

void ColliderGUI::Update()
{
	if (collider == nullptr)
		return;
	ImGui::Text("Collider");
	ImGui::BeginChild("##Collider", {300.f,100.f});
	sf::Vector2f position = collider->GetPosition();
	float Pos[2] = { position.x, position.y };
	ImGui::Text("position"); ImGui::SameLine();
	if (ImGui::InputFloat2("##position", Pos))
	{
		position.x = Pos[0];
		position.y = Pos[1];
		collider->SetPosition(position);
	}

	sf::Vector2f offsetPosition = collider->GetOffsetPosition();
	float offsetPos[2] = { offsetPosition.x, offsetPosition.y };
	sf::Vector2f colliderScale = collider->GetScale();
	float scaleArr[2] = { colliderScale.x, colliderScale.y };

	sf::Vector2f origin = collider->GetOrigin();
	float originArr[2] = { origin.x, origin.y };


	ImGui::Text("Position"); ImGui::SameLine();
	if (ImGui::InputFloat2("##Position", offsetPos))
	{
		offsetPosition.x = offsetPos[0];
		offsetPosition.y = offsetPos[1];
		collider->SetOffsetPosition(offsetPosition);
	}
	ImGui::Text("Scale   "); ImGui::SameLine();
	if (ImGui::InputFloat2("##Scale", scaleArr))
	{
		colliderScale.x = scaleArr[0];
		colliderScale.y = scaleArr[1];
		collider->SetScale(colliderScale);
	}

	ImGui::Text("Origin"); ImGui::SameLine();

	if (ImGui::InputFloat2("##Origin", originArr))
	{
		origin = { originArr[0], originArr[1] };
		collider->SetOrigin(origin);
	}
	//ImGui::Text("Rotation"); ImGui::SameLine();
	//if (ImGui::InputFloat("##Rotation", &rotation))
	//{
	//	targetObject->SetRotation(rotation);
	//}

	//ImGui::Text("Origin"); ImGui::SameLine();

	//if (ImGui::InputFloat2("##Origin", originArr))
	//{
	//	origin = { originArr[0], originArr[1] };
	//	collider->SetOrigin(origin);
	//}

	//static const OriginEnumDesc originEnum[] =
	//{
	//	{ Origins::TopLeft , "TopLeft"}
	//	,{ Origins::TopCenter , "TopCenter"}
	//	,{ Origins::TopRight , "TopRight"}
	//	,{ Origins::MiddleLeft , "MiddleLeft"}
	//	,{ Origins::MiddleCenter , "MiddleCenter"}
	//	, { Origins::MiddleRight , "MiddleRight"}
	//	,{ Origins::BottomLeft , "BottomLeft"}
	//	,{ Origins::BottomCenter , "BottomCenter"}
	//	,{ Origins::BottomRight , "BottomRight"}
	//	,{ Origins::Custom , "Custom"}
	//};

	//int idx;
	//for (idx = 0; idx < (int)Origins::Custom; ++idx)
	//{
	//	if (originEnum[idx].origin == (targetObject->GetOrigins()))
	//		break;
	//}

	//bool isSelect = false;
	//if (ImGui::BeginCombo("CurrentOrigin", originEnum[idx].originID.c_str()))
	//{
	//	for (int n = 0; n < (int)Origins::Custom; n++)
	//	{
	//		if (ImGui::Selectable(originEnum[n].originID.c_str(), idx == n))
	//		{
	//			targetObject->SetOrigin(originEnum[n].origin);
	//		}
	//	}

	//	ImGui::EndCombo();
	//}
	ImGui::EndChild();
}

void ColliderGUI::SetObject(GameObject* object)
{
	target = object;

	if (target == nullptr || target->GetCollider() == nullptr)
	{
		collider = nullptr;
		return;
	}

	collider = target->GetCollider();
}
