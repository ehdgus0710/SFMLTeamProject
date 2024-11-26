#pragma once
#include "DataTable.h"
#include "Variables.h"

class LangugeStringTable : public DataTable
{
public:
	static std::wstring Undefined;

protected:
	std::vector<std::unordered_map<std::string, std::wstring>> stringTables;
	std::unordered_map<std::string, std::wstring>* currentStringTableMap;

	std::string filePath = "tables/string_table.csv";
	std::vector<std::string> languageString;
public:
	const std::wstring& Get(const std::string& id, Languages language);
	const std::wstring& Get(const std::string& id);

	std::string LoadFilePath(int languagesIndex);
public:
	bool Load() override;
	void Release() override;

	LangugeStringTable();
	~LangugeStringTable();

};

