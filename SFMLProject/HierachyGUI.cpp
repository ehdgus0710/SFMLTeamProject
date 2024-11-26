#include "stdafx.h"
#include "HierachyGUI.h"

#include "ImguiManger.h"
#include "imgui.h"
#include "InspectorGUI.h"

#include "AnimationToolGUI.h"
#include "CollisionObjectEditor.h"
#include "CreateObjectTool.h"
#include "Scene.h"

HierachyGUI::HierachyGUI(const std::string& name)
    : GUI(name)
    , currentScene(nullptr)
    , currentObjectInspector(nullptr)
    , isOnAnimationTool(false)
    , isOnWallCollisionTool(false)
    , animationToolGUI(nullptr)
    , wallCollisionToolGUI(nullptr)
    , createObjectTool(nullptr)
    , isOnCreateObjectTool(false)
{
}

HierachyGUI::~HierachyGUI()
{
    if (animationToolGUI != nullptr)
        delete animationToolGUI;

    if (wallCollisionToolGUI != nullptr)
        delete wallCollisionToolGUI;

    if (createObjectTool != nullptr)
        delete createObjectTool;
}

void HierachyGUI::Init()
{
    animationToolGUI = new AnimationToolGUI;
    wallCollisionToolGUI = new CollisionObjectEditor;
    createObjectTool = new CreateObjectTool;

    createObjectTool->Init();
}

void HierachyGUI::Update()
{
	bool b = true;
    static int selected = -1;

	ImGui::Begin(GetName().c_str(), &b);

    currentScene = SceneManager::GetInstance().GetCurrentScene();
    const std::vector<std::vector<GameObject*>>& objectVectors = currentScene->GetObjectVectors();
    int size = (int)objectVectors.size();

    int currentPos = 0;

    for (int i = 0; i < size; ++i)
    {
        int objectCount = (int)objectVectors[i].size();
        for (int j = 0; j < objectCount; ++j)
        {
            const std::string& name = std::to_string(objectVectors[i][j]->GetID())+ ". " + objectVectors[i][j]->GetName();
            if (ImGui::Selectable(name.c_str(), selected == currentPos))
            {
                selected = currentPos;
                currentObjectInspector->SetObject(objectVectors[i][j]);
                currentObjectInspector->Activate();
                currentObjectInspector->Update();          

            }
            if (ImGui::BeginPopupContextItem())
            {
                selected = currentPos;
                ImGui::Text("Move Object", objectVectors[i][j]->GetName().c_str());
                if (ImGui::Button("MoveObject"))
                {
                    SceneManager::GetInstance().GetCurrentScene()->SetMoveFreeView(objectVectors[i][j]->GetPosition());
                    ImGui::CloseCurrentPopup();
                }

                ImGui::Text("Destory Object", objectVectors[i][j]->GetName().c_str());
                if (ImGui::Button("Delete"))
                {
                    objectVectors[i][j]->SetDestory(true);
                    ImGui::CloseCurrentPopup();
                }
                ImGui::EndPopup();
            }
            ImGui::SetItemTooltip("Right-click to open popup");
            ++currentPos;
        }
    }



   

    if (ImGui::Button("OnAnimaitonToolEditor", { 100, 20.f }))
        isOnAnimationTool = !isOnAnimationTool;

    if (isOnAnimationTool)
        animationToolGUI->Update();

    ImGui::SameLine();
    if (ImGui::Button("OnWallCollisionTool", { 100, 20.f }))
        isOnWallCollisionTool = !isOnWallCollisionTool;

    if (isOnWallCollisionTool)
        wallCollisionToolGUI->Update();

    ImGui::SameLine();
    if (ImGui::Button("OnCreateObjectTool", { 100, 20.f }))
        isOnCreateObjectTool = !isOnCreateObjectTool;

    if (isOnCreateObjectTool)
        createObjectTool->Update();
    
	ImGui::SameLine();
	if (ImGui::Button("Save", { 100, 20.f }))
	{
        SceneManager::GetInstance().GetCurrentScene()->Save(SceneManager::GetInstance().GetCurrentScene()->GetSavePath());
	}
	ImGui::SameLine();
	if (ImGui::Button("Load", { 100, 20.f }))
	{
        SceneManager::GetInstance().GetCurrentScene()->Load(SceneManager::GetInstance().GetCurrentScene()->GetLoadPath());
	}
	ImGui::End();
}

void HierachyGUI::Reset()
{
    currentObjectInspector->SetObject(nullptr);
}

