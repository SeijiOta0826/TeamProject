#include "PlayerPiece.h"

// Module関係
#include "Transform.h"
#include "Graphic.h"
#include "Collider.h"
#include "Gravity.h"

#include "Master.h"
#include "SceneManager.h"
#include "Scene.h"
#include "CollisionManager.h"

// ハブPlayer参照用
#include "Player.h"

#include "GameConfig.h"

PlayerPiece::PlayerPiece(Player* _player)
	: GameObject()
{
	// -- ハブのPlayerを設定 -- //
	mpPlayer = _player;
}

void PlayerPiece::Init()
{
	// -- タグ設定 -- //
	SetTag(Tag::PLAYER_CELL);
}

void PlayerPiece::InitComponent()
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

void PlayerPiece::Update(float _deltaTime)
{
	GameObject::Update(_deltaTime);
	ResolveStageCollision();
	UpdateWorldPosition();
}

void PlayerPiece::Draw()
{
	GameObject::Draw();
}

void PlayerPiece::SetEnabled(bool _enabled)
{
	if (auto transform = GetModule<Transform>())
		transform->SetEnabled(_enabled);
	
	if (auto graphic = GetModule<Graphic>())
		graphic->SetEnabled(_enabled);

	if (auto collider = GetModule<Collider>())
		collider->SetEnabled(_enabled);

	if (auto gravity = GetModule<Gravity>())
		gravity->SetEnabled(_enabled);
}

void PlayerPiece::UpdateWorldPosition()
{
	if (mpPlayer == nullptr)
		return;

	// -- 更新先の座標を取得 -- //
	auto player_transform = mpPlayer->GetModule<Transform>();
	VECTOR nextPos = VAdd(
		player_transform->GetPosition(),
		mvLocalPosition
	);

	// -- 座標を更新 -- //
	auto piece_transform = GetModule<Transform>();
	piece_transform->SetPosition(nextPos);
}

void PlayerPiece::ResolveStageCollision()
{
	mvCollisionCorrection = VGet(0.0f, 0.0f, 0.0f);
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

		mvCollisionCorrection = VAdd(
			mvCollisionCorrection,
			VScale(info.normal, info.penetration
			)
		);
	}


	auto playerTransform = mpPlayer->GetModule<Transform>();
	playerTransform->SetPosition(
		VAdd(
			playerTransform->GetPosition(),
			mvCollisionCorrection
		)
	);
}