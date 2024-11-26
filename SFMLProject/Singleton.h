#pragma once

template<typename T>
class Singleton
{
protected:
	static Singleton<T>* instance;
protected:
	Singleton() = default;
	virtual ~Singleton() = default; 
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;
public:
	static T& GetInstance();
};

template<typename T>
inline T& Singleton<T>::GetInstance()
{
	static T instance;
	return instance;
}
