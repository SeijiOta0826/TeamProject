#pragma once
#include "GameObject.h"
#include <array>

#include <DxLib.h>

class PlayerPiece;

class Player : public GameObject
{
public:
	Player();
	~Player();

	void Init() override;
	void InitComponent() override;
	void InitPiece();

	void Update(float _deltaTime) override;
	void Draw() override;

	// -- 角度(度数法)のアクセサ -- //
	void SetAngle(float _angle) { mfAngle = _angle; }
	float GetAngle() { return mfAngle; }

	void AddCollisionCorrection(VECTOR _correction);	// 修正値を集約する処理(主にPlayerPieceのResolve処理後、修正値が存在する場合に加算していく)
	void ResetCollisionCorrection();					// 修正値をリセットする処理(毎フレーム用いる)

	void ApplyCollisionCorrection();					// 修正値をPlayerへ適応する処理

private:
	void Move();
	void UpdatePiecePositions();	// 所有するPiece座標の更新

	// 変形画面を描画
	//void DrawTransformUI();
	//void UpdateTransformUI();

	// 変形後のColliderを更新
	//void UpdateTransformCollider();

protected:
	const char* GetModelFilename() const override {
		return "Resource/Player.png";
	}

private:
	int SIZE = 3;
	PlayerPiece* mPieces[3][3]{};
	bool mShape[3][3] = { true };			// 変形画面で選択するグリッドの配列
	bool mbIsTransforming = false;	// 変形中であることを示す

	float mfSpeed = 10.0f;		// 移動スピード

	float mfAngle = 0.0f;		// 回転の角度(-180 ~ 180)
	
	PlayerPiece* mpPiece;

	VECTOR mvCollisionCorrection = VGet(0.0f, 0.0f, 0.0f);	
	
	
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