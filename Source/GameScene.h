#pragma once
#include "Scene.h"

class Player_test;

class GameScene : public Scene
{
public:
    void Initialize() override;
    void Update(float deltaTime) override;
    void Draw() override;
    void Finalize() override;

private:
    Player_test* mpPlayer = nullptr;
};
