#include "stdafx.h"
#include "SavePointGUI.h"
#include "SavePointObject.h"
#include "imgui.h"

SavePointGUI::SavePointGUI()
	: ComponentGUI(ComponentGUIType::SavePoint)
{
}

SavePointGUI::~SavePointGUI()
{
}
void SavePointGUI::Update()
{
	if (savePoint == nullptr)
		return;
	ImGui::Text("SavePoint");
	ImGui::BeginChild("##SavePoint", { 200.f,100.f });

	sf::Vector2f restartPos = savePoint->GetRestartPosition();
	float Pos[2] = { restartPos.x, restartPos.y };

	ImGui::Text("RestartPosition"); ImGui::SameLine();
	if (ImGui::InputFloat2("##RestartPosition", Pos))
	{
		restartPos.x = Pos[0];
		restartPos.y = Pos[1];
		savePoint->SetRestartPosition(restartPos);
	}

	ImGui::EndChild();
}

void SavePointGUI::SetObject(GameObject* object)
{
	target = object;

	if (target == nullptr)
	{
		savePoint = nullptr;
		return;
	}

	savePoint = dynamic_cast<SavePointObject*>(target);
}

