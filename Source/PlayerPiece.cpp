#include "PlayerPiece.h"

PlayerPiece::PlayerPiece(std::string filename, VECTOR initPos)
	: GameObject(filename, initPos)
{
	// -- タグ設定 -- //
	SetTag(Tag::PLAYER_CELL);
}

void PlayerPiece::Update(float _deltaTime)
{

	GameObject::Update(_deltaTime);
}

void PlayerPiece::Draw()
{

	GameObject::Draw();
}