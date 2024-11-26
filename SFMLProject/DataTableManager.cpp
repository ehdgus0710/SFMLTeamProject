#include "stdafx.h"
#include "DataTableManager.h"


DataTableManger::~DataTableManger()
{
	Release();
}

void DataTableManger::Init()
{
	Release();

	tableMap.insert({ DataTable::Types::String, new StringTable() });

	for (auto table : tableMap)
	{
		table.second->Load();
	}
}

void DataTableManger::Release()
{
	for (auto table : tableMap)
	{
		table.second->Release();
		delete table.second;
	}

	tableMap.clear();
}
