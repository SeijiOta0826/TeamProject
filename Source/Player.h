#pragma once
#include "Object2D.h"

class Collider;
class Gravity; // ’Ç‰Á

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

private:
	Collider* mpCollider;

	Gravity* mpGravity; // ’Ç‰Á

	float mfSpeed = 10.0f;
};