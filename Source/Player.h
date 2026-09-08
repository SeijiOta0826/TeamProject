#pragma once
#include "Object2D.h"

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
	void ResolveStageCollision();

private:
	Collider* mpCollider;

	float mfSpeed = 10.0f;

private:
	float mCurrentAngle = 0.0f; // 今の角度（度数法：0?360）
	float mTargetAngle = 0.0f;  // 目指す角度

	const float BLOCK_SIZE = 100.0f; // ブロックのサイズ（仮定）
	float mMoveStepX = 0.0f; // 移動ステップ（仮定）

	void Rotate();

};