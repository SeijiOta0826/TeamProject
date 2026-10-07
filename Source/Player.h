#pragma once
#include "GameObject.h"
#include <array>

#include "PlayerController.h"

#include "GameConfig.h"

#include <DxLib.h>

class PlayerPiece;
class PlayerShapeUI;	// UI上の入力を取得する用

class Player : public GameObject
{
public:
	Player();
	~Player();

	void Init() override;
	void InitComponent() override;
	void InitPiece();	// Todo : これする場所確定させる

	void Update(float _deltaTime) override;
	void Draw() override;

	void Respawn();

private:
	void Move(VECTOR _direction);
	void Rotation(float _rotateDirection);

	void AddCollisionCorrection(VECTOR _correction);

	void SetShapeUI(PlayerShapeUI* _ui) { mpShapeUI = _ui; }
	void ApplyShapeFromUI();

	VECTOR mvRespawnPos = VGet(0.0f, 0.0f, 0.0f); 

	void CreatePiece(int _column, int _row);

	// -- 各Pieceの補正値を集約 & 適用 -- //
	void ResetCollisionCorrections();
	VECTOR CalculateCollisionCorrection();
	void ApplyCollisionCorrection();

	// -- Player座標補正後にPieceの座標を更新 -- //
	void UpdatePiecePosition();
	void UpdatePieceRotation();
protected:
	const char* GetModelFilename() const override {
		return "Resource/Player.png";
	}

private:
	PlayerPiece* mPieces[GameConfig::PLAYER_PIECE_SIZE][GameConfig::PLAYER_PIECE_SIZE]{};

	PlayerController mController;

	PlayerShapeUI* mpShapeUI;
	
	float mfSpeed = 10.0f;		// 移動スピード
	float mfAngle = 0.0f;		// 回転の角度(-180 ~ 180)
	float mfRotationPower = 5.0f;	// 回転力(単位は度数)
};