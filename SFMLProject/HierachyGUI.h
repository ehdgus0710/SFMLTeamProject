#pragma once
#include "GUI.h"

#include "Scene.h"
class InspectorGUI;

class HierachyGUI : public GUI
{
protected:
	Scene*					currentScene;
	InspectorGUI*			currentObjectInspector;
	GUI*					animationToolGUI;
	GUI*					wallCollisionToolGUI;
	GUI*					createObjectTool;

	bool					isOnAnimationTool;
	bool					isOnWallCollisionTool;
	bool					isOnCreateObjectTool;

public:
	virtual void Init();
	virtual void Update();
	void SetInspectorGUI(InspectorGUI* inspectorGUI) { currentObjectInspector = inspectorGUI; }
	void Reset() override;

public:
	HierachyGUI(const std::string& name);
	virtual ~HierachyGUI();
};

