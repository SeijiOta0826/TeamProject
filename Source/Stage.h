#pragma once
#include <string>
#include <vector>
#include <DxLib.h>

class Player;

class Stage
{
public:
	void Load(const std::string& _filename);

	VECTOR GetRespawnPos() const
	{
		return mvRespawnPos;
	}

	void SetPlayerRespawn(Player* _player);

private:
	void CreateObjects();

private:
	std::vector<std::vector<int>> mStageData;

	VECTOR mvRespawnPos = VGet(0.0f, 0.0f, 0.0f);
};