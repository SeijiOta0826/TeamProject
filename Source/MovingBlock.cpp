#include "MovingBlock.h"
#include "Player.h"
#include "Collider.h"

#include "Transform.h"

MovingBlock::MovingBlock(float leftLimit,float rightLimit,float speed)
    : StageBlock()
    , mfLeftLimit(leftLimit)
    , mfRightLimit(rightLimit)
    , mfSpeed(speed)
{

}

void MovingBlock::Init()
{
    // Playerとの衝突を取得する
    GetModule<Collider>()->AddCollisionTag(Tag::PLAYER);
}

void MovingBlock::Update(float _deltaTime)
{
    VECTOR previousPosition = GetModule<Transform>()->GetPosition();

    VECTOR position = previousPosition;

    if (mbMovingRight)
    {
        position.x += mfSpeed;
    }
    else
    {
        position.x -= mfSpeed;
    }

    if (position.x >= mfRightLimit)
    {
        position.x = mfRightLimit;
        mbMovingRight = false;
    }
    else if (position.x <= mfLeftLimit)
    {
        position.x = mfLeftLimit;
        mbMovingRight = true;
    }

    GetModule<Transform>()->SetPosition(position);

    // このフレームで実際に移動した量を保存
    mvMoveDelta = VSub(position, previousPosition);

    StageBlock::Update(_deltaTime);

    // 移動した分だけPlayerを運ぶ
    CarryPlayer();
}

void MovingBlock::CarryPlayer()
{
    if (VSize(mvMoveDelta) == 0.0f)
    {
        return;
    }

    auto collisions = GetModule<Collider>()->GetCollisions(Tag::PLAYER);

    for (auto* playerObject : collisions)
    {
        if (playerObject == nullptr)
        {
            continue;
        }

        Player* player = dynamic_cast<Player*>(playerObject);

        if (player == nullptr)
        {
            continue;
        }

        VECTOR playerPosition = player->GetModule<Transform>()->GetPosition();

        playerPosition = VAdd(
            playerPosition,
            mvMoveDelta
        );

        player->GetModule<Transform>()->SetPosition(playerPosition);
    }
}