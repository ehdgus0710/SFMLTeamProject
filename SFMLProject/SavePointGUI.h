#include "ComponentGUI.h"
class SavePointObject;

class SavePointGUI : public ComponentGUI
{
protected:
	SavePointObject* savePoint;

public:
	void Update() override;
	void SetObject(GameObject* object) override;

public:
	SavePointGUI();
	~SavePointGUI();
};