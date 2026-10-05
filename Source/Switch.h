#pragma once
#include "GameObject.h"

class Switch : public GameObject
{
public:
    Switch(std::string filename, VECTOR initPos);
    ~Switch() = default;

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