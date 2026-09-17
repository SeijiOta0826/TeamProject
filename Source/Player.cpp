#include "Player.h"

// Module関係
#include "Transform.h"
#include "Graphic.h"
#include "Collider.h"
#include "Gravity.h"

// Piece生成用
#include "Master.h"
#include "SceneManager.h"
#include "Scene.h"
#include "ObjectManager.h"
#include "PlayerPiece.h"

#include "GameConfig.h"

// 入力関係
#include "InputManager.h"

// ライブラリ
#include <DxLib.h>
#include <cmath>  //回転処理用

Player::Player()
	:GameObject()
{

	// 3×3 = 9個のColliderを作成
	//for (int i = 0; i < 9; i++)
	//{
	//	mColliders[i] = new GameObject("Resource/Player.png",VGet(0.0f,0.0f,0.0f));
	//	mColliders[i]->GetCollider()->AddCollisionTag(Tag::BLOCK);
	//	mColliders[i]->GetCollider()->SetHalfSize(
	//		VGet(
	//			GameConfig::CELL_SIZE / 2,
	//			GameConfig::CELL_SIZE / 2,
	//			0.0f
	//		)
	//	);

	//	mColliders[i]->GetCollider()->SetEnabled(false);
	//}

	//// 初期状態は中央の1ブロックだけ有効
	//mColliders[4]->GetCollider()->SetEnabled(true);

	//// 初期形状
	//mShape[1][1] = true;

	//UpdateTransformCollider();
}

Player::~Player()
{
	/*delete mpGravity;
	mpGravity = nullptr;

	for (auto* collider : mColliders)
	{
		if (collider != nullptr)
		{
			collider->GetCollider()->Finalize();
			delete collider;
		}
	}

	mColliders.fill(nullptr);*/
}

void Player::Init()
{
	// -- タグ設定 -- //
	SetTag(Tag::PLAYER);

	for (int column = 0;
		column < SIZE;
		column++)
	{
		for (int row = 0;
			row < SIZE;
			row++)
		{
			// -- Playerに基づく相対座標を取得 -- //
			VECTOR offset = VGet(0.0f, 0.0f, 0.0f);

			offset.x =
				(row - 1) * GameConfig::CELL_SIZE;

			offset.y =
				(column - 1) * GameConfig::CELL_SIZE;

			// -- Playerが保有するPieceの生成 & 初期設定-- //
			mPieces[row][column] =
				Master::mpSceneManager
				->GetCurrentScene()
				->GetObjectManager()
				->CreateObject<PlayerPiece>(this);

			mPieces[row][column]
				->SetLocalPosition(
					offset
				);
		}
	}
}

void Player::InitComponent()
{
	// -- Module追加 -- //
	AddModule<Transform>();
	/*AddModule<Graphic>();
	AddModule<Collider>();
	AddModule<Gravity>();*/

	// -- 衝突判定を取得するObjを指定 -- //
	/*auto collider = GetModule<Collider>();
	collider->AddCollisionTag(Tag::BLOCK);*/
}

void Player::Update(float _deltaTime)
{
	// Eキーを押したら変形モードに入る
	if (InputManager::GetInstance().GetButtonDown(Button::Transform))
	{
		mbIsTransforming = true;
	}

	// 変形中かどうかで入力を切り替える
	if (mbIsTransforming)
	{
		// UpdateTransformUI();
		return; //変形中は移動や重力処理を行わない
	}
	//else
	//{
	//	Move();

	//	// 通常時だけ重力を処理
	//	mpGravity->Update(_deltaTime);

	//	// StageBlockとの当たり判定
	//	ResolveStageCollision();
	//}
	//Rotate();//回転処理

	if (!mIsRolling)
	{
		Move();

		// StageBlockとの当たり判定
		//ResolveStageCollision();
	}

	GameObject::Update(_deltaTime);
}

void Player::Draw()
{
	//float rad = mCurrentAngle * (3.14159265f / 180.0f);
	//VECTOR centerPos = GetPosition();
	//const float blockSize = 100.0f;


	//if (mpTexture != nullptr)
	//{
	//	for (int y = 0; y < 3; y++)
	//	{
	//		for (int x = 0; x < 3; x++)
	//		{
	//			if (!mShape[y][x]) continue; // OFFのマスは描画しない

	//			// 中央(1, 1)からの相対座標
	//			float localX = (x - 1) * blockSize;
	//			float localY = (y - 1) * blockSize;

	//			// 2D回転行列で角度radに合わせて回転
	//			float rotatedX = localX * std::cos(rad) - localY * std::sin(rad);
	//			float rotatedY = localX * std::sin(rad) + localY * std::cos(rad);

	//			// 中心座標 + 回転後オフセット に描画
	//			DrawRotaGraphF(
	//				centerPos.x + rotatedX,
	//				centerPos.y + rotatedY,
	//				1.0,
	//				rad,
	//				mpTexture->GetHandle(),
	//				TRUE
	//			);
	//		}
	//	}
	//}

	// 変形画面
	/*if (mbIsTransforming)
	{
		DrawTransformUI();
	}*/

	GameObject::Draw();
}

void Player::Move()
{
	// -- 入力値を取得 -- //
	VECTOR inputDirection = VGet(0.0f, 0.0f, 0.0f);

	inputDirection.x += InputManager::GetInstance().GetAxis(Axis::MoveX);
	inputDirection.y += InputManager::GetInstance().GetAxis(Axis::MoveY);

	if (VSize(inputDirection) == 0.0f)
		return;

	// -- 移動量を取得 & 座標反映 -- //
	VECTOR moveAmount = VScale(inputDirection, mfSpeed);

	auto transform = GetModule<Transform>();
	VECTOR nextPos = VAdd(
		transform->GetPosition(),
		moveAmount
	);

	transform->SetPosition(nextPos);
}

//void Player::DrawTransformUI()
//{
//	int screenWidth;
//	int screenHeight;
//
//	GetDrawScreenSize(&screenWidth, &screenHeight);
//
//	const int cellSize = 100;
//	const int gridSize = cellSize * 3;
//
//	const int startX = (screenWidth - gridSize) / 2;
//	const int startY = (screenHeight - gridSize) / 2;
//
//	// 背景
//	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
//
//	DrawBox(
//		0,
//		0,
//		screenWidth,
//		screenHeight,
//		GetColor(0, 0, 0),
//		TRUE
//	);
//
//	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
//
//	// 3×3
//	for (int y = 0; y < 3; y++)
//	{
//		for (int x = 0; x < 3; x++)
//		{
//			int left = startX + x * cellSize;
//			int top = startY + y * cellSize;
//			int right = left + cellSize;
//			int bottom = top + cellSize;
//
//			int color;
//
//			if (mShape[y][x])
//			{
//				// ON
//				color = GetColor(255, 255, 255);
//			}
//			else
//			{
//				// OFF
//				color = GetColor(80, 80, 80);
//			}
//
//			DrawBox(
//				left,
//				top,
//				right,
//				bottom,
//				color,
//				TRUE
//			);
//
//			// 枠
//			DrawBox(
//				left,
//				top,
//				right,
//				bottom,
//				GetColor(255, 255, 255),
//				FALSE
//			);
//		}
//	}
//
//	DrawString(
//		startX,
//		startY - 40,
//		"変形",
//		GetColor(255, 255, 255)
//	);
//}
//
//void Player::UpdateTransformUI()
//{
//	int mouseX = InputManager::GetInstance().GetMouse().GetX();
//	int mouseY = InputManager::GetInstance().GetMouse().GetY();
//
//	const int cellSize = 100;
//	const int gridSize = cellSize * 3;
//
//	int screenWidth;
//	int screenHeight;
//
//	GetDrawScreenSize(&screenWidth, &screenHeight);
//
//	const int startX = (screenWidth - gridSize) / 2;
//	const int startY = (screenHeight - gridSize) / 2;
//
//	// マウスが3×3の範囲内にあるか
//	if (mouseX >= startX &&
//		mouseX < startX + gridSize &&
//		mouseY >= startY &&
//		mouseY < startY + gridSize)
//	{
//		// 何列目・何行目をクリックしたか計算
//		int cellX = (mouseX - startX) / cellSize;
//		int cellY = (mouseY - startY) / cellSize;
//
//		// 左クリックされたらON/OFF切り替え
//		if (InputManager::GetInstance().GetMouse().IsDown(MOUSE_INPUT_LEFT))
//		{
//			mShape[cellY][cellX] = !mShape[cellY][cellX];
//		}
//	}
//
//	// Enterで変形を確定
//	if (InputManager::GetInstance().GetButtonDown(Button::Confirm))
//	{
//		UpdateTransformCollider();
//
//		// 変形によって大きくなった場合のめり込み防止
//		VECTOR position = GetPosition();
//		position.y -= 10.0f;
//		SetPosition(position);
//
//		mbIsTransforming = false;
//	}
//}
//
//void Player::UpdateTransformCollider()
//{
//	const float blockSize = 100.0f;
//
//	for (int y = 0; y < 3; y++)
//	{
//		for (int x = 0; x < 3; x++)
//		{
//			int index = y * 3 + x;
//
//			GameObject* gameObject = mColliders[index];
//			Collider* collider = gameObject->GetCollider();
//
//			if (collider == nullptr)
//			{
//				continue;
//			}
//
//			// 選択されているマスだけColliderを有効にする
//			collider->SetEnabled(mShape[y][x]);
//
//			if (!mShape[y][x])
//			{
//				continue;
//			}
//
//			// 3×3の中心をPlayerの位置にする
//			float offsetX =
//				(x - 1) * blockSize;
//
//			float offsetY =
//				(y - 1) * blockSize;
//
//			// Colliderを各マスの位置へ移動
//			collider->SetOffset(
//				VGet(
//					offsetX,
//					offsetY,
//					0.0f
//				)
//			);
//
//			// 1ブロック分のCollider
//			collider->SetHalfSize(
//				VGet(
//					blockSize / 2.0f,
//					blockSize / 2.0f,
//					0.0f
//				)
//			);
//		}
//	}
//}
//
////=========回転処理=========
////=========回転処理=========
//void Player::Rotate()
//{
//	// 1. 押されているキーのチェック
//	bool isPressL = (CheckHitKey(KEY_INPUT_L) != 0);
//	bool isPressJ = (CheckHitKey(KEY_INPUT_J) != 0);
//
//	// まだ転がり始めていない時、キーが押されたら方向と開始位置を記録
//	if (!mIsRolling)
//	{
//		if (isPressL)
//		{
//			mDirection = 1.0f;       // 右
//			mIsRolling = true;
//			mRollTimer = 0;
//			mStartPos = GetPosition();
//			mStartAngle = mCurrentAngle;
//		}
//		else if (isPressJ)
//		{
//			mDirection = -1.0f;      // 左
//			mIsRolling = true;
//			mRollTimer = 0;
//			mStartPos = GetPosition();
//			mStartAngle = mCurrentAngle;
//		}
//	}
//
//	// 2. 転がりアニメーション（押し続け・離し判定）
//	if (mIsRolling)
//	{
//		// 該当する方向のキーが押され続けているか？
//		bool isHolding = (mDirection > 0.0f && isPressL) || (mDirection < 0.0f && isPressJ);
//
//		if (isHolding)
//		{
//			// 押し続けている間は進める
//			mRollTimer++;
//		}
//		else
//		{
//			// 離されたら巻き戻す（元の位置に戻る）
//			mRollTimer--;
//			if (mRollTimer <= 0)
//			{
//				mRollTimer = 0;
//				mIsRolling = false;
//				SetPosition(mStartPos);
//				mCurrentAngle = mStartAngle;
//				return;
//			}
//		}
//
//		// 進行度 t (0.0 〜 1.0)
//		float t = (float)mRollTimer / ROLL_FRAMES;
//
//		// 角度の更新
//		mCurrentAngle = mStartAngle + (90.0f * mDirection * t);
//
//		// 座標の更新
//		VECTOR pos = mStartPos;
//		pos.x += (BLOCK_SIZE * mDirection * t);
//
//		// 角の持ち上げ
//		float lift = std::sin(t * 3.14159265f) * 20.7f;
//		pos.y = mStartPos.y - lift;
//
//		SetPosition(pos);
//
//		// 完全に90度回しきった場合（押し続けた結果の完了処理）
//		if (mRollTimer >= ROLL_FRAMES)
//		{
//			mIsRolling = false;
//			mRollTimer = 0;
//
//			pos.y = mStartPos.y;
//			pos.x = mStartPos.x + (BLOCK_SIZE * mDirection);
//			SetPosition(pos);
//
//			mCurrentAngle = 0.0f;
//
//			// --- 3×3 配列 mShape を90度回転 ---
//			bool tempShape[3][3];
//			for (int y = 0; y < 3; y++) {
//				for (int x = 0; x < 3; x++) {
//					if (mDirection > 0.0f) {
//						tempShape[x][2 - y] = mShape[y][x]; // 時計回り
//					}
//					else {
//						tempShape[2 - x][y] = mShape[y][x]; // 反時計回り
//					}
//				}
//			}
//
//			// 配列を上書きしてColliderを再配置
//			for (int y = 0; y < 3; y++) {
//				for (int x = 0; x < 3; x++) {
//					mShape[y][x] = tempShape[y][x];
//				}
//			}
//			UpdateTransformCollider();
//		}
//	}
//}


