#pragma once
#include "Scene.h"

class Player;
class Goal;

class GameScene : public Scene
{
public:
    void Initialize();
    void Update(float deltaTime);
    void Draw();
    void Finalize();

    private:
		int mFontHandle = -1; // �t�H���g�n���h��

    void SetStageNumber(int _stageNumber);

private:
    int mnStageNumber = 1;

    bool mbIsPaused = false;
    bool mbPreviousP = false;
    bool mbPreviousMouseLeft = false;

    void UpdatePause();
    void DrawPause();
    void DrawClear();
    void UpdateClear();

    Player* mpPlayer = nullptr;
    bool mbIsClear = false;

    Goal* mpGoal = nullptr;
};
