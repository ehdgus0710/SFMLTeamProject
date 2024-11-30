#pragma once
#include "GUI.h"
class MenuGUI :
    public GUI
{
protected:
	Scene* currentScene;
public:
	virtual void Init();
	virtual void Update();
	void Reset() override;

public:
	MenuGUI(const std::string& name);
	virtual ~MenuGUI();
};

