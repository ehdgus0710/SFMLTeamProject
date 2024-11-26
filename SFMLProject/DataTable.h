#pragma once
class DataTable
{
public:
	enum class Types
	{
		String,
		Zombie,
		Item,
	};
	static const int TotalTypes = 1;

protected:
	Types type;

public:
	virtual bool Load() = 0;
	virtual void Release() = 0;

	virtual void Init();

public:
	DataTable(Types type);
	virtual ~DataTable() = default;
};

