#pragma once
#include <string>
#include <vector>

class Stage
{
public:
	void Load(const std::string& _filename);

private:
	void CreateObjects();

private:
	std::vector<std::vector<int>> mStageData;
};