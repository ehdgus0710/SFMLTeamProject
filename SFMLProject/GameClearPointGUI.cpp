#include "stdafx.h"
#include "GameClearPointGUI.h"
#include "GameClearObject.h"
#include "imgui.h"

GameClearPointGUI::GameClearPointGUI()
	: ComponentGUI(ComponentGUIType::GameClearPoint)
	, clearObject(nullptr)
{
}

GameClearPointGUI::~GameClearPointGUI()
{
}
void GameClearPointGUI::Update()
{
	if (clearObject == nullptr)
		return;
	ImGui::Text("ClearPoint");
	ImGui::BeginChild("##ClearPoint", { 300.f,100.f });

	sf::Vector2f maxStartPosition = clearObject->GetMaxStartPosition();
	float maxStartPos[2] = { maxStartPosition.x, maxStartPosition.y };

	ImGui::Text("MaxStartPosition"); ImGui::SameLine();
	if (ImGui::InputFloat2("##MaxStartPosition", maxStartPos))
	{
		maxStartPosition.x = maxStartPos[0];
		maxStartPosition.y = maxStartPos[1];
		clearObject->SetMaxStartPosition(maxStartPosition);
	}

	 sf::Vector2f destinationPosition = clearObject->GetDestinationPosition();
	 float Pos[2] = { destinationPosition.x, destinationPosition.y };
	 
	 ImGui::Text("DestinationPosition"); ImGui::SameLine();
	 if (ImGui::InputFloat2("##DestinationPosition", Pos))
	 {
		 destinationPosition.x = Pos[0];
		 destinationPosition.y = Pos[1];
		 clearObject->SetDestinationPosition(destinationPosition);
	 }
	 sf::Vector2f endMovePosition = clearObject->GetEndMovePosition();
	 float endMovePos[2] = { endMovePosition.x, endMovePosition.y };

	 ImGui::Text("EndMovePosition"); ImGui::SameLine();
	 if (ImGui::InputFloat2("##EndMovePosition", endMovePos))
	 {
		 endMovePosition.x = endMovePos[0];
		 endMovePosition.y = endMovePos[1];
		 clearObject->SetEndMovePosition(endMovePosition);
	 }
	ImGui::EndChild();
}

void GameClearPointGUI::SetObject(GameObject* object)
{
	target = object;

	if (target == nullptr)
	{
		clearObject = nullptr;
		return;
	}

	clearObject = dynamic_cast<GameClearObject*>(target);
}
