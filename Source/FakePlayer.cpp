#include "FakePlayer.h"

// -- Module -- //
#include "Transform.h"
#include "Graphic.h"
#include "Collider.h"
#include "Gravity.h"

#include "Master.h"
#include "SceneManager.h"
#include "Scene.h"
#include "CollisionManager.h"

#include "InputManager.h"

#include "GameConfig.h"

void FakePlayer::Init()
{

}

void FakePlayer::InitComponent()
{
	// -- Module追加 -- //
	AddModule<Transform>();
	AddModule<Graphic>(GetModelFilename());
	AddModule<Collider>();
	AddModule<Gravity>();

	// -- 衝突判定を取得するObjを指定 -- //
	auto collider = GetModule<Collider>();
	collider->AddCollisionTag(Tag::BLOCK);
	collider->SetHalfSize(VGet(GameConfig::CELL_SIZE / 2.0f, GameConfig::CELL_SIZE / 2.0f, 0.0f));
}

void FakePlayer::Finalize()
{

}

void FakePlayer::Update(float _deltaTime)
{
	if (InputManager::GetInstance().GetButtonDown(Button::OperationChange_toPlayer))
		InputManager::GetInstance().SetInputMode(InputMode::Normal);

	GameObject::Update(_deltaTime);

	Move();
	ResolveStageCollision();
}

void FakePlayer::Draw()
{
	GameObject::Draw();
}

void FakePlayer::Move()
{
	// -- 入力値を取得 -- //
	VECTOR inputDirection = VGet(0.0f, 0.0f, 0.0f);

	inputDirection.x += InputManager::GetInstance().GetAxis(Axis::MoveX_FAKE);
	inputDirection.y += InputManager::GetInstance().GetAxis(Axis::MoveY_FAKE);

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

void FakePlayer::ResolveStageCollision()
{
	VECTOR collisionCorrection = VGet(0.0f, 0.0f, 0.0f);
	// nullCheack
	auto myTransform = GetModule<Transform>();
	auto myCollider = GetModule<Collider>();
	if (!myTransform
		|| !myCollider)
		return;

	// 有効check
	if (!myTransform->IsEnabled()
		|| !myCollider->IsEnabled())
		return;

	Tag tag = Tag::BLOCK;
	auto objects = myCollider->GetCollisions(tag);
	for (auto obj : objects)
	{
		// -- 衝突objのCollider取得 & nullCheck -- //
		auto collider = obj->GetModule<Collider>();
		if (!collider)
			continue;

		CollisionInfo info;
		if (!Master::mpSceneManager
			->GetCurrentScene()
			->GetCollisionManager()
			->GetBoxBoxCollision(
				myCollider,
				collider,
				info)
			)
		{
			continue;
		}

		if (info.normal.y < -0.5f)
			mbGrounded = true;

		collisionCorrection = VAdd(
			collisionCorrection,
			VScale(info.normal, info.penetration
			)
		);
	}


	auto transform = this->GetModule<Transform>();
	transform->SetPosition(
		VAdd(
			transform->GetPosition(),
			collisionCorrection
		)
	);
}