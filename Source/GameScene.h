#pragma once
#include "Scene.h"

class GameScene : public Scene
{
public:
    void Initialize();
    void Update(float deltaTime);
    void Draw();
    void Finalize();
};
