#pragma once
class GUI
{
private:
	std::string		name;
	bool			isActive;

public:
	void SetName(const std::string& _strName) { name = _strName; }
	const std::string& GetName() { return name; }

public:
	virtual void Init() {}
	virtual void Update() = 0;

public:
	virtual void Activate() { isActive = true; }
	void Deactivate() { isActive = false; }
	bool IsActive() { return isActive; }
	virtual void Reset() {};

public:
	GUI(const std::string& name);
	virtual ~GUI();
};
