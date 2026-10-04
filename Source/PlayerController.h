#pragma once

class Player;

class PlayerController
{
public:
	PlayerController() = default;
	~PlayerController() = default;

	void Initialize(Player* _player);	// 初期処理(主にPlayer設定)
	void Update();

	void UpdateMove();
	void UpdateOperationChange();
	void UpdateRotation();

private:
	Player* mpPlayer;
};