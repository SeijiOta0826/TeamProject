#include "GameScene.h"

#include "Master.h"
#include "SceneManager.h"
#include "Scene.h"
#include "ObjectManager.h"

#include "Stage.h"
#include "Player.h"
#include "StageBlock.h"

#include "Debug.h"
#include "GameConfig.h"


void GameScene::Initialize()
{
    // 初期化処理
    auto* player =
        this
        ->GetObjectManager()
        ->CreateObject<Player>();
    player->InitPiece();

    auto* stage = new Stage();
    stage->Load("Resource/Stage/test_stage.csv");

}

void GameScene::Update(float deltaTime)
{
    //mpPlayer->Update();
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

    //mpPlayer->Draw();
    Debug::Draw();
    Scene::Draw();
}

void GameScene::Finalize()
{
    // 終了処理
    Scene::Finalize();
}