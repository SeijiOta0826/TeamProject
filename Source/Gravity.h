#pragma once
#include "Module.h"

class GameObject;

class Gravity : public Module
{
public:
	void Update(float _deltaTime);

private:
	void ResetVerticalVelocity();	// 落下速度を「0」にする

private:
	float mfVelocityY = 0.0f;		// 落下速度
};
