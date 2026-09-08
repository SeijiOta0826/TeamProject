#include "Player.h"

#include "Collider.h"
#include "InputManager.h"

#include "Master.h"
#include "SceneManager.h"
#include "Scene.h"
#include "CollisionManager.h"

#include "StageBlock.h"
#include "Texture.h"

Player::Player(std::string filename, VECTOR initPos)
	: Object2D(filename, initPos)
{
	SetTag(Tag::PLAYER);

	mpCollider = new Collider(this);
	mpCollider->Initialize();

	mpCollider->SetHalfSize(VGet(50.0f, 50.0f, 0.0f));
}

void Player::Update(float _deltaTime)
{
	// 回転・転がり処理
	Rotate();

	// 転がっている最中は矢印キーなどの通常移動を止める
	if (mCurrentAngle == mTargetAngle)
	{
		Move();
	}

	ResolveStageCollision();
}

void Player::Draw()
{
	// 度数法(0?360)をラジアンに変換
	float rad = mCurrentAngle * (3.14159265f / 180.0f);

	VECTOR pos = GetPosition();

	if (mpTexture != nullptr)
	{
		DrawRotaGraphF(pos.x, pos.y, 1.0, rad, mpTexture->GetHandle(), TRUE);
	}
}

void Player::Move()
{
	VECTOR inputDirection = VGet(0.0f, 0.0f, 0.0f);

	inputDirection.x += InputManager::GetInstance().GetAxis(Axis::MoveX);
	inputDirection.y += InputManager::GetInstance().GetAxis(Axis::MoveY);

	if (VSize(inputDirection) == 0.0f)
		return;

	VECTOR moveAmount = VScale(inputDirection, mfSpeed);

	VECTOR nextPos = VAdd(
		GetPosition(),
		moveAmount
	);

	SetPosition(nextPos);
}

void Player::ResolveStageCollision() 
{
	auto* collisionManager =
		Master::mpSceneManager
		->GetCurrentScene()
		->GetCollisionManager();

	auto* collider = mpCollider;

	auto* stage =
		collider->GetCollision(Tag::BLOCK);

	if (stage == nullptr) {
		return;
	}

	auto StageObj =
		dynamic_cast<StageBlock*>(stage);

	auto* stageCollider =
		StageObj->GetCollider();

	if (stageCollider == nullptr) {
		return;
	}

	CollisionInfo info;

	if (!collisionManager->GetBoxBoxCollision(
		collider,
		stageCollider,
		info)) {
		return;
	}

	VECTOR position =
		this->GetPosition();

	position = VAdd(
		position,
		VScale(info.normal, info.penetration)
	);

	this->SetPosition(position);
}

void Player::Rotate()
{
	// 1. 静止中（回転していない時）に入力を受け付ける
	if (mCurrentAngle == mTargetAngle)
	{
		// Lキーで右にゴロンと1ブロック転がる
		if (CheckHitKey(KEY_INPUT_L)) {
			mTargetAngle += 90.0f;
			// 30フレームかけて90度回すので、1フレームあたり (BLOCK_SIZE / 30) 進める
			mMoveStepX = BLOCK_SIZE / 30.0f;
		}
		// Jキーで左にゴロンと1ブロック転がる
		else if (CheckHitKey(KEY_INPUT_J)) {
			mTargetAngle -= 90.0f;
			mMoveStepX = -BLOCK_SIZE / 30.0f;
		}
	}

	// 2. 右へ転がる処理
	if (mCurrentAngle < mTargetAngle)
	{
		mCurrentAngle += 3.0f; // 角度を進める

		// 座標も同時に進める
		VECTOR pos = GetPosition();
		pos.x += mMoveStepX;
		SetPosition(pos);

		if (mCurrentAngle >= mTargetAngle) {
			mCurrentAngle = mTargetAngle;
		}
	}
	// 3. 左へ転がる処理
	else if (mCurrentAngle > mTargetAngle)
	{
		mCurrentAngle -= 3.0f; // 角度を戻す

		// 座標も同時に戻す
		VECTOR pos = GetPosition();
		pos.x += mMoveStepX;
		SetPosition(pos);

		if (mCurrentAngle <= mTargetAngle) {
			mCurrentAngle = mTargetAngle;
		}
	}
}