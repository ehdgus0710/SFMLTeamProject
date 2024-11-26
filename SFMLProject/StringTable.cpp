#include "stdafx.h"
#include "StringTable.h"
#include "rapidcsv.h"

std::wstring StringTable::Undefined = L"Undefined Id";

StringTable::StringTable()
    : DataTable(Types::String)
{
}

StringTable::~StringTable()
{
}

const std::wstring& StringTable::Get(const std::string& id)
{
    auto iter = stringTableMap.find(id);

    if (iter == stringTableMap.end())
    {
        return Undefined;
    }

    return iter->second;
}

std::string StringTable::LoadFilePath()
{
    return filePath;
}

bool StringTable::Load()
{
    if (!stringTableMap.empty())
        return false;

    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;

    rapidcsv::Document doc(LoadFilePath(), rapidcsv::LabelParams(0, -1));

    for (int i = 0; i < doc.GetRowCount(); ++i)
    {
        auto strings = doc.GetRow<std::string>(i);
        auto iter = stringTableMap.find(strings[0]);
        if (iter != stringTableMap.end())
        {
            std::cout << "스트링 테이블 키 중복" << std::endl;
            return false;
        }

        stringTableMap.insert({ strings[0], converter.from_bytes(strings[1]) });
    }
    return true;
}

void StringTable::Release()
{
    stringTableMap.clear();
}
