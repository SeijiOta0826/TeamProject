#pragma once
#include "GameObject.h"

class FakePlayer : public GameObject
{
public:
	FakePlayer() = default;
	~FakePlayer() = default;

	void Init() override;
	void InitComponent() override;
	void Finalize() override;
	void Update(float _deltaTime) override;
	void Draw() override;
};