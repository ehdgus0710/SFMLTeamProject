#include "ComponentGUI.h"
#include "AnimationToolGUI.h"

class AnimationGUI : public ComponentGUI
{
protected:
	std::vector<std::string> nameVectors;
	Animator*			animator;
	// AnimationToolGUI*	animationTool;
	// bool				useAnimationTool;
public:
	virtual void Update();
	void SetObject(GameObject* object);

public:
	AnimationGUI();
	~AnimationGUI();
};