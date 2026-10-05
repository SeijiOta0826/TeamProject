#include "SwitchBlock.h"

#include "Switch.h"
#include "Collider.h"
#include "Gravity.h"

SwitchBlock::SwitchBlock(
    std::string filename,
    VECTOR initPos,
    Switch* _switch
)
    : StageBlock(filename, initPos)
    , mpSwitch(_switch)
{
    // 最初は非表示・当たり判定OFF
    mbIsVisible = false;
    mpCollider->SetEnabled(false);

    // 重力は使わない
    mpGravity->SetEnable(false);
}

void SwitchBlock::Update(float _deltaTime)
{
    if (_deltaTime <= 0.0f)
        return;

    if (mpSwitch != nullptr && mpSwitch->IsActivated())
    {
        mbIsVisible = true;
        mpCollider->SetEnabled(true);
    }

    if (mbIsVisible)
    {
        StageBlock::Update(_deltaTime);
    }
}

void SwitchBlock::Draw()
{
    if (!mbIsVisible)
        return;

    StageBlock::Draw();
}