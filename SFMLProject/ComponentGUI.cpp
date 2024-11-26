#include "stdafx.h"
#include "ComponentGUI.h"

ComponentGUI::ComponentGUI(ComponentGUIType type)
	: type(type)
	, target(nullptr)
{
}

ComponentGUI::~ComponentGUI()
{
}