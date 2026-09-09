#pragma once
#include "Object2D.h"
#include <array>

class Collider;
class Gravity; // 追加

class Player : public Object2D
{
public:
	Player(std::string filename, VECTOR initPos);
	~Player();

	void Update(float _deltaTime) override;
	void Draw() override;

private:
	void Move();
	void ResolveStageCollision();
	
	// 変形画面を描画
	void DrawTransformUI();
	void UpdateTransformUI();

	// 変形後のColliderを更新
	void UpdateTransformCollider();

private:
	std::array<Collider*, 9> mColliders;

	Gravity* mpGravity; // 追加

	bool mbIsTransforming = false; // 追加

	// 3×3の形状データ
	bool mShape[3][3] = {};

	float mfSpeed = 10.0f;
};