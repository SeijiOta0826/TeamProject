#pragma once
#include <vector>
#include <string>

class CsvLoader
{
public:
	static std::vector<std::vector<int>> Load(const std::string& _filename);
};