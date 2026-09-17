#include "PlayerPiece.h"

// Module関係
#include "Transform.h"
#include "Graphic.h"
#include "Collider.h"
#include "Gravity.h"

// ハブPlayer参照用
#include "Player.h"

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
	AddModule<Graphic>();
	AddModule<Collider>();
	AddModule<Gravity>();

	// -- 衝突判定を取得するObjを指定 -- //
	auto collider = GetModule<Collider>();
	collider->AddCollisionTag(Tag::BLOCK);
}

void PlayerPiece::Update(float _deltaTime)
{
	UpdateWorldPosition();
	GameObject::Update(_deltaTime);
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