#pragma once
#include "GameObject.h"

class Spike : public GameObject
{
public:
    ~Spike() = default;

    void Init() override;

    void Update(float _deltaTime) override;
    void Draw() override;

private:
    void CheckPlayerCollision();
};