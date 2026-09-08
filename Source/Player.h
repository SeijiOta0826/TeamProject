#pragma once
#include "Object2D.h"

class Collider;
class Gravity; // �ǉ�

class Player : public Object2D
{
public:
	Player(std::string filename, VECTOR initPos);
	~Player();

	void Update(float _deltaTime) override;
	void Draw() override;

private:
	void Move();
	void ResolveStageCollision();	// ステージとの衝突判定を受け取り、移動を制限する処理

private:
	Collider* mpCollider;		// このオブジェクトが使用するコライダー
		
	float mfSpeed = 10.0f;		// 移動スピード(移動はPlayerくらいしかしないかな...と思ったのでPlayer持ち)

	Gravity* mpGravity; // �ǉ�
};