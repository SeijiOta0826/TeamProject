#pragma once
#include "StageBlock.h"

class Player;

class DisappearingBlock : public StageBlock
{
public:
	void Init() override;

	void Update(float _deltaTime) override;
	void Draw() override;

private:
	bool CheckPlayer();
	void Disappear();
	void Respawn();

private:
	int mTimer = 0;

	// プレイヤーが乗り続ける時間
	const int DISAPPEAR_TIME = 180;

	// 消える前の警告時間
	const int WARNING_TIME = 60;

	// プレイヤーが離れてから復活するまでの時間
	const int RESPAWN_TIME = 120;

	bool mbIsTriggered = false;
	bool mbIsDisappeared = false;
	bool mbIsWarning = false;
	bool mbIsPlayerLeft = false;

	Player* mpPlayer = nullptr;
};