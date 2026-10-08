#pragma once
#include "StageBlock.h"

class Switch;

class SwitchBlock : public StageBlock
{
public:
    SwitchBlock(Switch* _switch);
    ~SwitchBlock() = default;

    void Init() override;
    void Update(float _deltaTime) override;
    void Draw() override;

private:
    Switch* mpSwitch = nullptr;
    bool mbIsVisible = false;
};