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
		column < 1;
		column++)
	{
		for (int row = 0;
			row < 1;
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

	if (!mIsRolling)
	{
		Move();
	}

	GameObject::Update(_deltaTime);
}

void Player::Draw()
{
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