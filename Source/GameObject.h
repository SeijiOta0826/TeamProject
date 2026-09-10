#pragma once
#include "Object2D.h"

class Collider;
class Gravity;

class GameObject : public Object2D
{
public:
	GameObject(std::string filename, VECTOR initPos);
	~GameObject();

	void Update(float _deltaTime) override;
	void Draw() override;

private:
	Collider* mpCollider;		// コライダー
	Gravity* mpGravity;			// 重力
};