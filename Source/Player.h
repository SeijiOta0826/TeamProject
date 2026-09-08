#pragma once
#include "Object2D.h"
#include "GameConfig.h"

class Collider;

class Player : public Object2D
{
public:
	Player(std::string filename, VECTOR initPos);
	~Player() = default;

	void Update(float _deltaTime) override;
	void Draw() override;

private:
	void Move();
	void ResolveStageCollision();	// ステージとの衝突判定を受け取り、移動を制限する処理

private:
	Collider* mpCollider;

	float mfSpeed = 10.0f;

	float mCurrentAngle = 0.0f; // 現在の角度
	float mTargetAngle = 0.0f;  // 目標の角度

	const float BLOCK_SIZE = GameConfig::CELL_SIZE;
	float mMoveStepX = 0.0f;	// 回転に伴う移動値

	void Rotate();
};