#pragma once
#include "GameObject.h"

class PlayerPiece : public GameObject
{
public:
	PlayerPiece(std::string filename, VECTOR initPos);
	~PlayerPiece() = default;

	void Update(float _deltaTime) override;
	void Draw() override;
};