#include "stdafx.h"
#include "AnimationGUI.h"
#include "imgui.h"
#include "Animator.h"
#include "Animation.h"

AnimationGUI::AnimationGUI()
	: ComponentGUI(ComponentGUIType::Animator)
	, animator(nullptr)
	// , useAnimationTool(true)
{
	// animationTool = new AnimationToolGUI;
}

AnimationGUI::~AnimationGUI()
{
	// delete animationTool;
}

void AnimationGUI::Update()
{
    if (animator == nullptr)
        return;
    ImGui::BeginChild("##Animation", { 300.f,150.f });

    ImGui::Text("Animation");
    Animation* animation = animator->GetCurrentAnimation();
    if (animation)
    {
        std::vector<AnimationInfo> AnimationInfoVecs = animation->GetFrameInfo();
        // int iFrmID = pAnimation->GetFrmIdx();
        // float fAccTime = pAnimation->GetAccTime();
        // wstring wstrName = pAnimation->GetName();
        // string strName = string(wstrName.begin(), wstrName.end());

        static ImGuiComboFlags flags = 0;

        std::unordered_map<std::string, Animation*> mapAnim = animator->GetMap();

        nameVectors.clear();
        for (auto iter = mapAnim.begin(); iter != mapAnim.end(); iter++)
        {
            nameVectors.push_back(iter->first);
        }

        static int item_current_idx = 0; // Here we store our selection data as an index.
        if (ImGui::BeginCombo("##Animation", nameVectors[item_current_idx].c_str(), flags))
        {
            for (int n = 0; n < nameVectors.size(); n++)
            {
                const bool is_selected = (item_current_idx == n);
                if (ImGui::Selectable(nameVectors[n].c_str(), is_selected))
                {
                    item_current_idx = n;
                    animator->ChangeAnimation(nameVectors[n], true);
                }

                // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndCombo();
        }
        ImGui::EndChild();
    }
}

void AnimationGUI::SetObject(GameObject* object)
{
	target = object;

	if (target == nullptr || target->GetAnimator() == nullptr)
	{
		animator = nullptr;
		return;
	}

	animator = target->GetAnimator();
	

}