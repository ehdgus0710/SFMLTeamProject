#include "stdafx.h"
#include "Core.h"
#include "Framework.h"
int main()
{

    Framework framework;
    WindowManager::GetInstance().init({ 1920, 1080 }, "haha");
    auto renderWindow = WindowManager::GetInstance().GetRenderWindow();
    
    framework.Init();
    framework.Update();
     
    // _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    return 0;
}