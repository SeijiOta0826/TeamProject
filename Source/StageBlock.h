#pragma once
#include "GameObject.h"

class StageBlock : public GameObject
{
public:
	StageBlock(std::string filename, VECTOR initPos);
	~StageBlock() = default;

	void Update(float _deltaTime) override;
	void Draw() override;
};