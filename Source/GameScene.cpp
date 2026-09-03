#include "GameScene.h"
#include "ScreenConfig.h"
#include <DxLib.h>

void GameScene::Initialize()
{
    // 初期化処理
}

void GameScene::Update(float deltaTime)
{
    // 更新処理
}

void GameScene::Draw()
{
    // 例　GameScene 描画処理

    // 背景
    DrawBox(
        0,
        0,
        1920,
        1080,
        GetColor(30, 30, 30),
        TRUE
    );

    // 仮のプレイヤー
    DrawCircle(
        960,
        540,
        50,
        GetColor(0, 150, 255),
        TRUE
    );

    // 仮の文字
    DrawString(
        20,
        20,
        "GAME SCENE",
        GetColor(255, 255, 255)
    );
}

void GameScene::Finalize()
{
    // 終了処理
}