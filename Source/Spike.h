#pragma once
#include "GameObject.h"

class Spike : public GameObject
{
public:
    Spike(std::string filename, VECTOR initPos);
    ~Spike() = default;

    void Update(float _deltaTime) override;
    void Draw() override;

private:
    void CheckPlayerCollision();
};