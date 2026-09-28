#pragma once
#include "StageBlock.h"

class Player;

class MovingBlock : public StageBlock
{
public:
    MovingBlock(
        std::string filename,
        VECTOR initPos,
        float leftLimit,
        float rightLimit,
        float speed
    );

    ~MovingBlock() = default;

    void Update(float _deltaTime) override;

    // このフレームでどれだけ移動したか取得
    VECTOR GetMoveDelta() const
    {
        return mvMoveDelta;
    }

    // プレイヤーを移動床の移動量だけ運ぶ
    void CarryPlayer();

private:
    float mfLeftLimit;
    float mfRightLimit;
    float mfSpeed;

    bool mbMovingRight = true;

    VECTOR mvMoveDelta = VGet(0.0f, 0.0f, 0.0f);
};