#include "stdafx.h"
#include "MenuGUI.h"
#include "imgui.h"

MenuGUI::MenuGUI(const std::string& name)
	: GUI("Menu")
    , currentScene(nullptr)
{
}

MenuGUI::~MenuGUI()
{
}

void MenuGUI::Init()
{
}

void MenuGUI::Update()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("Scene"))
        {
            if (ImGui::BeginMenu("ChangeScene"))
            {
                if (ImGui::MenuItem("SceneDev1"))
                {
                    SceneManager::GetInstance().ChangeScene(SceneIds::SceneDev1);
                }
                if (ImGui::MenuItem("SceneDev2"))
                {
                    SceneManager::GetInstance().ChangeScene(SceneIds::SceneDev2);
                }
                if (ImGui::MenuItem("SceneDev3"))
                {
                    SceneManager::GetInstance().ChangeScene(SceneIds::SceneDev3);
                }
                if (ImGui::MenuItem("Stage1"))
                {
                    SceneManager::GetInstance().ChangeScene(SceneIds::Stage1);
                }
                if (ImGui::MenuItem("Stage2"))
                {
                    SceneManager::GetInstance().ChangeScene(SceneIds::Stage2);
                }
                if (ImGui::MenuItem("Stage3"))
                {
                    SceneManager::GetInstance().ChangeScene(SceneIds::Stage3);
                }
                if (ImGui::MenuItem("TitleScene"))
                {
                    SceneManager::GetInstance().ChangeScene(SceneIds::TitleScene);
                }
                ImGui::EndMenu();
            }
            // IMGUI_DEMO_MARKER("Menu/File");
            // ShowExampleMenuFile();
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

void MenuGUI::Reset()
{
}
