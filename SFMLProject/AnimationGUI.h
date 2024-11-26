#include "ComponentGUI.h"
#include "AnimationToolGUI.h"

class AnimationGUI : public ComponentGUI
{
protected:
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