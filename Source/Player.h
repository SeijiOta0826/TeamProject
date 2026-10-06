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

	void Move(VECTOR _direction);
	void Rotation(float _rotateDirection);

	void BeginCollisionResolution() override;
	void EndCollisionResolution() override;

	// -- 角度(度数法)のアクセサ -- //
	void SetAngle(float _angle) { mfAngle = _angle; }
	float GetAngle() { return mfAngle; }

	void AddCollisionCorrection(VECTOR _correction);

	

private:
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

	std::vector<VECTOR> mCollisionCorrections;
	
	// --- 転がり・回転用メンバ変数 ---
    bool mIsRolling = false;          // 転がり中フラグ
    int mRollTimer = 0;               // 経過フレーム（0〜30）
    const int ROLL_FRAMES = 30;       // 転がりにかかるフレーム数（約0.5秒）
    const float BLOCK_SIZE = 100.0f;  // 1マスのサイズ（HalfSizeが50なら100）

    float mDirection = 0.0f;          // 向き（右: 1.0f / 左: -1.0f）
    VECTOR mStartPos = VGet(0, 0, 0); // 開始時の座標
    float mStartAngle = 0.0f;         // 開始時の角度
    float mCurrentAngle = 0.0f;       // 現在の描画角度

    // void Rotate();                    // 転がり関数の宣言

	
};