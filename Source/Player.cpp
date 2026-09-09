#include "Player.h"

#include "Collider.h"
#include "Gravity.h" 
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

	// �ǉ�
	mpGravity = new Gravity(this);
	mpGravity->Initialize();
}

Player::~Player()
{
	delete mpGravity;
	mpGravity = nullptr;

	delete mpCollider;
	mpCollider = nullptr;
}

void Player::Update(float _deltaTime)
{

	// ��]�E�]���菈��
	Rotate();

	// �]�����Ă���Œ��͖��L�[�Ȃǂ̒ʏ�ړ����~�߂�
	if (mCurrentAngle == mTargetAngle)
	{
		Move();
	}

	Move();

	mpGravity->Update(_deltaTime); // �ǉ�

	ResolveStageCollision();
}

void Player::Draw()
{
	// �x���@(0?360)�����W�A���ɕϊ�
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
	//----1フレームあたりの回転角と移動量
	// 例: 30フレームで90度・1ブロック分動かす場合
	const float ROTATE_SPEED = 3.0f; //90f / 30f
	const float MOVE_SPEED = BLOCK_SIZE / 30.0f; //1ブロック分 / 30フレーム

	float angleDelta = 0.0f;
	float moveDelta = 0.0f;

	if (CheckHitKey(KEY_INPUT_L))
	{
		angleDelta = ROTATE_SPEED;
		moveDelta = MOVE_SPEED;
	}

	else if (CheckHitKey(KEY_INPUT_J))
	{
		angleDelta = -ROTATE_SPEED;
		moveDelta = -MOVE_SPEED;
	}

	//入力がある場合のみ回転する
	if (angleDelta != 0.0f)
	{
		mCurrentAngle += angleDelta;

		if (mCurrentAngle >= 360.0f)mCurrentAngle -= 360.0f;
		if (mCurrentAngle < 0.0f)   mCurrentAngle += 360.0f;


		VECTOR pos = GetPosition();
		pos.x += moveDelta;
		SetPosition(pos);


	}


}

