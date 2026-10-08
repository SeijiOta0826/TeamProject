#include "Goal.h"
#include "Collider.h"
#include "Player.h"

Goal::Goal(
    std::string filename,
    VECTOR initPos,
    const bool _shape[3][3]
)
    :GameObject(filename, initPos)
{
    for (int y = 0; y < 3; y++)
    {
        for (int x = 0; x < 3; x++)
        {
            mShape[y][x] = _shape[y][x];
        }
    }

	SetTag(Tag::GOAL);

	mpCollider->SetHalfSize(
		VGet(50.0f, 50.0f, 0.0f)
	);

	// ƒvƒŒƒCƒ„[‚Æ‚ÌÕ“Ë‚ðŒ©‚é
	mpCollider->AddCollisionTag(Tag::PLAYER);
}

Goal::~Goal()
{
}

void Goal::Update(float _deltaTime)
{
}

void Goal::Draw()
{
	Object2D::Draw();
}

bool Goal::IsPlayerTouching() const
{
	return mpCollider->IsColliding(Tag::PLAYER);
}

bool Goal::IsShapeMatched(Player* _player) const
{
    if (_player == nullptr)
        return false;

    for (int row = 0; row < 3; row++)
    {
        for (int column = 0; column < 3; column++)
        {
            if (_player->HasPiece(row, column) != mShape[row][column])
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

    VECTOR playerPos = _player->GetPosition();
    VECTOR goalPos = GetPosition();

    float distance = VSize(
        VSub(playerPos, goalPos)
    );

    const float clearDistance = 50.0f;

    return distance <= clearDistance;
}