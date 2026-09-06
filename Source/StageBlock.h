#pragma once
#include "Object2D.h"

class Collider;

class StageBlock : public Object2D
{
public:
	StageBlock(std::string filename, VECTOR initPos);
	~StageBlock() = default;

	void Update(float _deltaTime) override;
	void Draw() override;

	Collider* GetCollider() { return mpCollider; }

private:
	Collider* mpCollider;
};