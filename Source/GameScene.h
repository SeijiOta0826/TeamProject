#pragma once
#include "Scene.h"

class GameScene : public Scene
{
public:
    void Initialize();
    void Update(float deltaTime);
    void Draw();
    void Finalize();

    void SetStageNumber(int _stageNumber);

private:
    int mnStageNumber = 1;
};