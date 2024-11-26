#pragma once
#include "GUI.h"
#include "GameObject.h"

class ComponentGUI;

struct OriginEnumDesc
{
	Origins origin;
	std::string originID;
};

static const OriginEnumDesc originEnum[] =
{
	{ Origins::TopLeft , "TopLeft"}
	,{ Origins::TopCenter , "TopCenter"}
	,{ Origins::TopRight , "TopRight"}
	,{ Origins::MiddleLeft , "MiddleLeft"}
	,{ Origins::MiddleCenter , "MiddleCenter"}
	, { Origins::MiddleRight , "MiddleRight"}
	,{ Origins::BottomLeft , "BottomLeft"}
	,{ Origins::BottomCenter , "BottomCenter"}
	,{ Origins::BottomRight , "BottomRight"}
	,{ Origins::Custom , "Custom"}
};

class InspectorGUI : public GUI
{
protected:
	GameObject*					targetObject;
	std::vector<ComponentGUI*>	componetGUIvector;

private:
	void TransformInfo();

public:
	virtual void Init();
	virtual void Update();
	void SetObject(GameObject* object);

public:
	InspectorGUI(const std::string& name);
	virtual ~InspectorGUI();
};

