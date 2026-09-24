#pragma once
#include "Scene.h"
#include <cstddef>
#include "DxLib.h"

#include "FloatingMotion.h"//＜－－－追加
#include "UILabel.h"

class Player;
class Goal;

class GameScene : public Scene
{
public:
    void Initialize();
    void Update(float deltaTime);
    void Draw();
    void Finalize();
    void SetStageNumber(int _stageNumber);

private:
		int mFontHandle = -1; // フォントハンドル
		
        void*  mAddedFontHandle = nullptr; // フォントハンドル

    int mCursorHandle = -1;

    void DrawCursor();

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

    //FontやTitleLogoなどのアニメーションをするためのコンポジション
private:

    UILabel mStageTextMotion; //Stage用
    FloatingMotion mClearTextMotion; //Clear用


};
