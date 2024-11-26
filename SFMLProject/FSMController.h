#pragma once

#include "BaseState.h"

template<typename T>
class FSMController
{
protected:
	std::unordered_map<T, BaseState<T>*> stateMap;
	T currentStateType;
	T preiousStateType;


public:
	T GetCurrentStateType() { return currentStateType; }
	T GetPreiousStateType() { return preiousStateType; }

public:
	virtual void AddState(T type);
	virtual BaseState<T>* CreateState(T type) = 0;
	virtual void ChangeState(T type);

public:
	virtual void Awake() {}
	virtual void Start() {}

	virtual void Update(float deltaTime) = 0;
	virtual void FixedUpdate(float fixedDeltaTime) = 0;
	virtual void LateUpdate(float deltaTime) = 0;

public:
	FSMController();
	virtual ~FSMController();
};

template<typename T>
inline void FSMController<T>::AddState(T type)
{
	auto iter = stateMap.find(type);
	if (stateMap.end() == iter)
	{
		stateMap.insert({ type, CreateState(type) });
	}
}

template<typename T>
inline void FSMController<T>::ChangeState(T type)
{
	auto iter = stateMap.find(type);
	if (iter != stateMap.end())
	{
		stateMap[currentStateType]->Exit();
		preiousStateType = currentStateType;
		currentStateType = type;
		stateMap[currentStateType]->Enter();
	}
}

template<typename T>
inline FSMController<T>::FSMController()
{
}

template<typename T>
inline FSMController<T>::~FSMController()
{

	for (auto state : stateMap)
	{
		state.second->Release();
		delete state.second;
	}

	stateMap.clear();
}
