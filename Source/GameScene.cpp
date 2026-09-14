#include "GameScene.h"

#include "Master.h"
#include "SceneManager.h"
#include "Scene.h"
#include "ObjectManager.h"

#include "Stage.h"
#include "Player.h"
#include "StageBlock.h"

#include <string>
#include "Debug.h"
#include "GameConfig.h"


void GameScene::Initialize()
{
    // 初期化処理
    auto* player =
       this
        ->GetObjectManager()
        ->CreateObject<Player>(
            "Resource/Player.png",
            VGet(120.0f, 500.0f, 0.0f)
        );

    auto* stage = new Stage();

    /*if (mnStageNumber == 1)
    {
        stageFileName = "Resource/Stage/test_stage.csv";
    }

    stage->Load(stageFileName);*/
    
    std::string stageFileName =
        "Resource/Stage/Stage"
        + std::to_string(mnStageNumber)
        + ".csv";

    stage->Load(stageFileName);

    // ステージを増やす際はCSVの名前を Stage1.csv Stage2.csv … にしとけば読み込んでくれる
}

void GameScene::Update(float deltaTime)
{
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

void GameScene::SetStageNumber(int _stageNumber)
{
    mnStageNumber = _stageNumber;
}

void GameScene::Finalize()
{
    // 終了処理
}