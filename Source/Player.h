#pragma once
#include "Object2D.h"
#include <array>

class Collider;
class Gravity; // 追加

class Player : public Object2D
{
public:
	Player(std::string filename, VECTOR initPos);
	~Player();

	void Update(float _deltaTime) override;
	void Draw() override;

private:
	void Move();
	void ResolveStageCollision();	// ステージとの衝突判定を受け取り、移動を制限する処理

private:
	Collider* mpCollider;		// このオブジェクトが使用するコライダー
	Gravity* mpGravity; // 追加


	float mfSpeed = 10.0f;		// 移動スピード(移動はPlayerくらいしかしないかな...と思ったのでPlayer持ち)
	
	// 変形画面を描画
	void DrawTransformUI();
	void UpdateTransformUI();

	// 変形後のColliderを更新
	void UpdateTransformCollider();

private:
	std::array<Collider*, 9> mColliders;

	bool mbIsTransforming = false; // 追加

	// 3×3の形状データ
	bool mShape[3][3] = {};

private:
	private:
    // --- 転がり・回転用メンバ変数 ---
    bool mIsRolling = false;          // 転がり中フラグ
    int mRollTimer = 0;               // 経過フレーム（0〜30）
    const int ROLL_FRAMES = 30;       // 転がりにかかるフレーム数（約0.5秒）
    const float BLOCK_SIZE = 100.0f;  // 1マスのサイズ（HalfSizeが50なら100）

    float mDirection = 0.0f;          // 向き（右: 1.0f / 左: -1.0f）
    VECTOR mStartPos = VGet(0, 0, 0); // 開始時の座標
    float mStartAngle = 0.0f;         // 開始時の角度
    float mCurrentAngle = 0.0f;       // 現在の描画角度

    void Rotate();                    // 転がり関数の宣言
};