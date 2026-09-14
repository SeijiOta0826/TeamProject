#pragma once
#include "GameObject.h"

class Player_test;

class PlayerPiece : public GameObject
{
public:
	PlayerPiece(Player_test* player, std::string filename, VECTOR initPos);
	~PlayerPiece() = default;

	void Update(float _deltaTime) override;
	void Draw() override;

	// -- Playerからの相対座標アクセサ -- //
	void SetLocalPosition(VECTOR _pos) { mvLocalPosition = _pos; }
	VECTOR GetLocalPosition() { return mvLocalPosition; }

	void SetEnabled(bool _enabled);
private:
	void UpdateWorldPosition();
private:
	Player_test* mpPlayer;
	VECTOR mvLocalPosition;	// Playerからの相対座標
};