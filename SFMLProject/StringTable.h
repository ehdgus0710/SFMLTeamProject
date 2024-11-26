#pragma once
#include "DataTable.h"

class StringTable : public DataTable
{
public:
	static std::wstring Undefined;

protected:
	std::unordered_map<std::string, std::wstring> stringTableMap;
	
	std::string filePath;
	std::vector<std::string> languageString;
public:
	const std::wstring& Get(const std::string& id);

	std::string LoadFilePath();
public:
	bool Load() override;
	void Release() override;

	StringTable();
	~StringTable();

};

