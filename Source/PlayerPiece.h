#pragma once
#include "GameObject.h"

#include <DxLib.h>	// VECTOR用

class Player;

class PlayerPiece : public GameObject
{
public:
	PlayerPiece(Player* _player);
	~PlayerPiece() = default;

	void Init() override;
	void InitComponent() override;

	void Update(float _deltaTime) override;
	void Draw() override;

	// -- Playerからの相対座標アクセサ -- //
	void SetLocalPosition(VECTOR _pos) { mvLocalPosition = _pos; }
	VECTOR GetLocalPosition() { return mvLocalPosition; }

	void SetEnabled(bool _enabled);	// 有効状態のセッター
private:
	void UpdateWorldPosition();
private:
	Player* mpPlayer = nullptr;	// ハブとなるPlayerのポインタ

	VECTOR mvLocalPosition = VGet(0.0f, 0.0f, 0.0f);		// Playerからの相対座標
};