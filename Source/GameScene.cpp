#include "GameScene.h"

#include "Master.h"
#include "SceneManager.h"
#include "Scene.h"
#include "ObjectManager.h"

#include "Stage.h"
#include "Player.h"
#include "Player_test.h"
#include "StageBlock.h"

#include "Debug.h"
#include "GameConfig.h"


void GameScene::Initialize()
{
    // 初期化処理
    /*auto* player =
       this
        ->GetObjectManager()
        ->CreateObject<Player>(
            "Resource/Player.png",
            VGet(0.0f, 0.0f, 0.0f)
        );*/

    auto* stage = new Stage();
    stage->Load("Resource/Stage/test_stage.csv");

    mpPlayer =
        new Player_test();
}

void GameScene::Update(float deltaTime)
{
    mpPlayer->Update();
    // 更新処理
    Scene::Update(deltaTime);
}

void GameScene::Draw()
{
    DrawBox(
        0, 0,
        1280, 720,
        GetColor(217, 198, 143),
        TRUE
    );

    Debug::Draw();
    Scene::Draw();
}

void GameScene::Finalize()
{
    // 終了処理
    Scene::Finalize();
}