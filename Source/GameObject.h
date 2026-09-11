#pragma once
#include "Object2D.h"

class Collider;
class Gravity;

class GameObject : public Object2D
{
public:
	GameObject(std::string filename, VECTOR initPos);
	virtual ~GameObject();

	virtual void Update(float _deltaTime) override;
	virtual void Draw() override;

	Collider* GetCollider() { return mpCollider; }
	Gravity* GetGravity() { return mpGravity; }

	bool IsGrounded() { return mbGrounded; }
private:
	void ResolveCollision();	// ステージとの衝突判定を受け取り、移動を制限する処理

protected:
	Collider* mpCollider;		// コライダー
	Gravity* mpGravity;			// 重力

	bool mbGrounded = false;	// 接地状態を示す
};