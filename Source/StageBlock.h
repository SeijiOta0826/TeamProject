#pragma once
#include "GameObject.h"

class Collider;

class StageBlock : public GameObject
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