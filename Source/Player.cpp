#include "Player.h"

#include "Collider.h"
#include "Gravity.h" // �ǉ�
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
	// 1. �Î~���i��]���Ă��Ȃ����j�ɓ��͂��󂯕t����
	if (mCurrentAngle == mTargetAngle)
	{
		// L�L�[�ŉE�ɃS������1�u���b�N�]����
		if (CheckHitKey(KEY_INPUT_L)) {
			mTargetAngle += 90.0f;
			// 30�t���[��������90�x�񂷂̂ŁA1�t���[�������� (BLOCK_SIZE / 30) �i�߂�
			mMoveStepX = BLOCK_SIZE / 30.0f;
		}
		// J�L�[�ō��ɃS������1�u���b�N�]����
		else if (CheckHitKey(KEY_INPUT_J)) {
			mTargetAngle -= 90.0f;
			mMoveStepX = -BLOCK_SIZE / 30.0f;
		}
	}

	// 2. �E�֓]���鏈��
	if (mCurrentAngle < mTargetAngle)
	{
		mCurrentAngle += 3.0f; // �p�x��i�߂�

		// ���W�������ɐi�߂�
		VECTOR pos = GetPosition();
		pos.x += mMoveStepX;
		SetPosition(pos);

		if (mCurrentAngle >= mTargetAngle) {
			mCurrentAngle = mTargetAngle;
		}
	}
	// 3. ���֓]���鏈��
	else if (mCurrentAngle > mTargetAngle)
	{
		mCurrentAngle -= 3.0f; // �p�x��߂�

		// ���W�������ɖ߂�
		VECTOR pos = GetPosition();
		pos.x += mMoveStepX;
		SetPosition(pos);

		if (mCurrentAngle <= mTargetAngle) {
			mCurrentAngle = mTargetAngle;
		}
	}
}