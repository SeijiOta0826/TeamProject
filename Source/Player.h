#pragma once
#include "GameObject.h"
#include <array>

class Collider;
class Gravity;

class Player : public GameObject
{
public:
	Player(std::string filename, VECTOR initPos);
	~Player();

	void Update(float _deltaTime) override;
	void Draw() override;

private:
	void Move();

	// 変形画面を描画
	void DrawTransformUI();
	void UpdateTransformUI();

	// 変形後のColliderを更新
	void UpdateTransformCollider();

private:
	float mfSpeed = 10.0f;		// 移動スピード

	std::array<Collider*, 9> mColliders;	// Playerが保有するColliderの配列	

	bool mShape[3][3] = {};			// 変形画面で選択するグリッドの配列
	bool mbIsTransforming = false;	// 変形中であることを示す
};