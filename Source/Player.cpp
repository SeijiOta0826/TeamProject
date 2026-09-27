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

}

Player::~Player()
{

}

void Player::Init()
{
	// -- タグ設定 -- //
	SetTag(Tag::PLAYER);
}

void Player::InitComponent()
{
	// -- Module追加 -- //
	AddModule<Transform>();
}

void Player::InitPiece()
{
	// Todo : 複数Pieceに対応させる
	
	// -- piece生成 & 初期処理 -- //
	mpPiece = Master::mpSceneManager
		->GetCurrentScene()
		->GetObjectManager()
		->CreateObject<PlayerPiece>(this);

	if (auto transform = GetModule<Transform>())
		mpPiece->SetLocalPosition(VGet(0.0f, 0.0f, 0.0f));
}

void Player::Update(float _deltaTime)
{
	GameObject::Update(_deltaTime);

	Move();						// 移動処理
	UpdatePiecePositions();		// Pieceの座標を更新

	ResetCollisionCorrection();
	mpPiece->ResolveStageCollision();

	ApplyCollisionCorrection();
	UpdatePiecePositions();		// Pieceの座標を更新
}

void Player::Draw()
{
	GameObject::Draw();
}

void Player::AddCollisionCorrection(VECTOR _correction)
{
	if (fabsf(_correction.x) > fabsf(mvCollisionCorrection.x))
	{
		mvCollisionCorrection.x = _correction.x;
	}

	if (fabsf(_correction.y) > fabsf(mvCollisionCorrection.y))
	{
		mvCollisionCorrection.y = _correction.y;
	}

	if (fabsf(_correction.z) > fabsf(mvCollisionCorrection.z))
	{
		mvCollisionCorrection.z = _correction.z;
	}
}

void Player::ResetCollisionCorrection()
{
	mvCollisionCorrection = VGet(0.0f, 0.0f, 0.0f);
}

void Player::ApplyCollisionCorrection()
{
	auto transform = GetModule<Transform>();
	transform->SetPosition(
		VAdd(
			transform->GetPosition(),
			mvCollisionCorrection
		)
	);
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

void Player::UpdatePiecePositions()
{
	// Todo : 複数Pieceに対応させる
	mpPiece->UpdateWorldPosition();
}



