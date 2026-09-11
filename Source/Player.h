#pragma once
#include "GameObject.h"
#include <array>

class Collider;
class Gravity;

class Player : public GameObject
{
public:
	Player(std::string filename, VECTOR initPos);
	~Player();

	void Update(float _deltaTime) override;
	void Draw() override;

private:
	void Move();

	// 変形画面を描画
	void DrawTransformUI();
	void UpdateTransformUI();

	// 変形後のColliderを更新
	void UpdateTransformCollider();

private:
	float mfSpeed = 10.0f;		// 移動スピード

	std::array<Collider*, 9> mColliders;	// Playerが保有するColliderの配列	

	bool mShape[3][3] = {};			// 変形画面で選択するグリッドの配列
	bool mbIsTransforming = false;	// 変形中であることを示す

    // --- 転がり・回転用メンバ変数 ---
    bool mIsRolling = false;          // 転がり中フラグ
    int mRollTimer = 0;               // 経過フレーム（0〜30）
    const int ROLL_FRAMES = 45;       // 転がりにかかるフレーム数（約0.5秒）<= この数値をいじると回転スピードが変わる
    const float BLOCK_SIZE = 100.0f;  // 1マスのサイズ（HalfSizeが50なら100）

    float mDirection = 0.0f;          // 向き（右: 1.0f / 左: -1.0f）
    VECTOR mStartPos = VGet(0, 0, 0); // 開始時の座標
    float mStartAngle = 0.0f;         // 開始時の角度
    float mCurrentAngle = 0.0f;       // 現在の描画角度

	bool mbCompleteRoll = false;		// 最後まで回りきるかどうかのフラグ

    void Rotate();                    // 転がり関数の宣言
};