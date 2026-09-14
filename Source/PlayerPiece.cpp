#include "PlayerPiece.h"

#include "Player_test.h"

#include "Collider.h"
#include "Gravity.h"

PlayerPiece::PlayerPiece(Player_test* player, std::string filename, VECTOR initPos)
	: GameObject(filename, initPos)
{
	// -- タグ設定 -- //
	SetTag(Tag::PLAYER_CELL);

	mpPlayer = player;
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
	if (auto* collider = GetCollider())
	{
		collider->SetEnabled(_enabled);
	}

	if (auto* gravity = GetGravity())
	{
		gravity->SetEnabled(_enabled);
	}
}

void PlayerPiece::UpdateWorldPosition()
{
	if (mpPlayer == nullptr)
		return;

	SetPosition(
		VAdd(
			mpPlayer->GetPosition(),
			mvLocalPosition
		)
	);
}