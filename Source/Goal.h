#pragma once

#include "GameObject.h"

class Goal : public GameObject
{
public:
	Goal(std::string filename, VECTOR initPos);
	~Goal();

	void Update(float _deltaTime) override;
	void Draw() override;

	bool IsPlayerTouching() const;
};