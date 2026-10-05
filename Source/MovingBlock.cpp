#include "MovingBlock.h"
#include "Player.h"
#include "Collider.h"

MovingBlock::MovingBlock(std::string filename,VECTOR initPos,float leftLimit,float rightLimit,float speed)
    : StageBlock(filename, initPos)
    , mfLeftLimit(leftLimit)
    , mfRightLimit(rightLimit)
    , mfSpeed(speed)
{
    // Player‚Æ‚ÌÕ“Ë‚ðŽæ“¾‚·‚é
    mpCollider->AddCollisionTag(Tag::PLAYER);
}

void MovingBlock::Update(float _deltaTime)
{
    VECTOR previousPosition = GetPosition();

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

    SetPosition(position);

    // ‚±‚ÌƒtƒŒ[ƒ€‚ÅŽÀÛ‚ÉˆÚ“®‚µ‚½—Ê‚ð•Û‘¶
    mvMoveDelta = VSub(position, previousPosition);

    StageBlock::Update(_deltaTime);

    // ˆÚ“®‚µ‚½•ª‚¾‚¯Player‚ð‰^‚Ô
    CarryPlayer();
}

void MovingBlock::CarryPlayer()
{
    if (VSize(mvMoveDelta) == 0.0f)
    {
        return;
    }

    auto collisions = mpCollider->GetCollisions(Tag::PLAYER);

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

        VECTOR playerPosition = player->GetPosition();

        playerPosition = VAdd(
            playerPosition,
            mvMoveDelta
        );

        player->SetPosition(playerPosition);
    }
}