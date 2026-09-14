#pragma once
#include <DxLib.h>

class PlayerPiece;

class Player_test
{
public:
	Player_test();
	~Player_test();

	void Update();
	void Draw();

	void Move();

	// -- 座標のアクセサ -- //
	void SetPosition(VECTOR _pos) { mvPosition = _pos; }
	VECTOR GetPosition() { return mvPosition; }

private:
	// 変形画面を描画
	void DrawTransformUI();
	void UpdateTransformUI();

	void UpdateTransformCollider();
private:
	int SIZE = 3;
	PlayerPiece* mPieces[3][3]{};
	bool mShape[3][3] = {true};			// 変形画面で選択するグリッドの配列
	VECTOR mvPosition = VGet(0.0f, 0.0f, 0.0f);
	bool mbIsTransforming = false;	// 変形中であることを示す


	float mfSpeed = 10.0f;		// 移動スピード
};