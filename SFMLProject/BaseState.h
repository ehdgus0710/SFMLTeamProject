#pragma once

template<typename T>
class BaseState
{
protected:
	T stateType;

public:
	virtual void Awake() {}
	virtual void Start() {}
	virtual void Release() {}

	virtual void Enter() = 0;
	virtual void Exit() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void FixedUpdate(float fixedDeltaTime) = 0;
	virtual void LateUpdate(float deltaTime) = 0;

	T GetCurrentState() { return stateType; }

public:
	BaseState(T type);
	virtual ~BaseState();
};

template<typename T>
inline BaseState<T>::BaseState(T type)
	: stateType(type)
{
}

template<typename T>
inline BaseState<T>::~BaseState()
{
}
