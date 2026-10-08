#pragma once
#include "GameObject.h"

class Switch : public GameObject
{
public:
    ~Switch() = default;

    void Init() override;
    void InitComponent() override {}
    void Update(float _deltaTime) override;

    bool IsActivated() const
    {
        return mbIsActivated;
    }

private:
    void CheckPlayer();

private:
    bool mbIsActivated = false;
};