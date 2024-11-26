#pragma once

#include "GameObject.h"

class UITextGameObject;
class UICoinObject;

class InGameUIHub : public GameObject
{
protected:
	std::unordered_map<std::string, UITextGameObject*> uiTextGameObjectMaps;

	UITextGameObject*	scoreNameUI;
	UITextGameObject*	worldNameUI;
	UITextGameObject*	timeNameUI;
	UITextGameObject*	marioNameUI;
	UITextGameObject*	scoreUI;
	UITextGameObject*	worldUI;
	UITextGameObject*	timerUI;
	UITextGameObject*	coinUI;
	UICoinObject*		coinAnimationUI;
	std::string			fontId;



private:
	void PushBackObject();

public:
	void Start() override;
	void OnAllDisable();
	void OnAllActive();

	std::unordered_map<std::string, UITextGameObject*>& GetTextGameObjectMaps() { return uiTextGameObjectMaps; }
	UITextGameObject* GetTextGameObject(const std::string& name);
public:
	sf::FloatRect GetLocalBounds() const;
	sf::FloatRect GetGlobalBounds() const;

public:
	InGameUIHub(const std::string& textId, const std::string& name);
	virtual ~InGameUIHub() = default;
};

