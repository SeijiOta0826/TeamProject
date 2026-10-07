#include "Goal.h"
#include "Player.h"

#include "Transform.h"
#include "Collider.h"

Goal::Goal()
{
   /* for (int y = 0; y < 3; y++)
    {
        for (int x = 0; x < 3; x++)
        {
            mShape[y][x] = _shape[y][x];
        }
    }

	SetTag(Tag::GOAL);

	mpCollider->SetHalfSize(
		VGet(50.0f, 50.0f, 0.0f)
	);*/

	// プレイヤーとの衝突を見る
	GetModule<Collider>()->AddCollisionTag(Tag::PLAYER);
}

Goal::~Goal()
{
}

void Goal::Update(float _deltaTime)
{
}

void Goal::Draw()
{

}

bool Goal::IsPlayerTouching()
{
	return GetModule<Collider>()->IsColliding(Tag::PLAYER);
}

bool Goal::IsShapeMatched(Player* _player) const
{
    if (_player == nullptr)
        return false;

    const bool* playerShape = _player->GetShape();

    for (int y = 0; y < 3; y++)
    {
        for (int x = 0; x < 3; x++)
        {
            if (playerShape[y * 3 + x] != mShape[y][x])
            {
                return false;
            }
        }
    }

    return true;
}

bool Goal::IsWithinDistance(Player* _player)
{
    if (_player == nullptr)
        return false;

    VECTOR playerPos = _player->GetModule<Transform>()->GetPosition();
    VECTOR goalPos = GetModule<Transform>()->GetPosition();

    float distance = VSize(
        VSub(playerPos, goalPos)
    );

    const float clearDistance = 50.0f;

    return distance <= clearDistance;
}