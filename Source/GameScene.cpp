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
        ->CreateObject<Player>(
            "Resource/Player.png",
            VGet(120.0f, 500.0f, 0.0f)
        );

    auto* stage = new Stage();
    stage->Load("Resource/Stage/test_stage.csv");

    //const int STAGE_HEIGHT = 5;
    //const int STAGE_WIDTH = 12;

    //int stageData[STAGE_HEIGHT][STAGE_WIDTH] = {
    //    {0,0,0,0,0,0,0,0,0,0,0,0}, // 空中足場
    //    {0,0,0,0,0,0,0,0,1,1,1,1},
    //    {0,0,0,0,0,1,0,0,0,0,0,0},
    //    {0,0,0,0,0,0,0,0,0,0,0,0},
    //    {0,1,1,1,0,0,0,0,0,0,0,0}, // 地面
    //};

    //// ブロック1つあたりのサイズ
    //const float BLOCK_SIZE = 112.0f;

    //// 描画の基準となる左上の開始座標
    //const float START_X = -55.0f;
    //const float START_Y = 215.0f;

    //// 配列をループして、1の場所にブロックを生成する
    //for (int y = 0; y < STAGE_HEIGHT; ++y)
    //{
    //    for (int x = 0; x < STAGE_WIDTH; ++x)
    //    {
    //        if (stageData[y][x] == 1)
    //        {
    //            // 配列のインデックス(x, y)から、実際のワールド座標(posX, posY)を計算
    //            float posX = START_X + (x * BLOCK_SIZE);
    //            float posY = START_Y + (y * BLOCK_SIZE);

    //            this->GetObjectManager()->CreateObject<StageBlock>(
    //                "Resource/Stage.png",
    //                VGet(posX, posY, 0.0f)
    //            );
    //        }
    //    }
    //}

    //auto block =
    //    Master::mpSceneManager
    //    ->GetCurrentScene()
    //    ->GetObjectManager()
    //    ->CreateObject<StageBlock>(
    //        "Resource/Obj/test_field.png",
    //        VGet(300.0f, 300.0f, 0.0f)
    //    );

    //// 配列をループして、1の場所にブロックを生成する
    //for (int y = 0; y < STAGE_HEIGHT; ++y)
    //{
    //    for (int x = 0; x < STAGE_WIDTH; ++x)
    //    {
    //        if (stageData[y][x] == 1)
    //        {
    //            // 配列のインデックス(x, y)から、実際のワールド座標(posX, posY)を計算
    //            float posX = START_X + (x * BLOCK_SIZE);
    //            float posY = START_Y + (y * BLOCK_SIZE);

    //            this->GetObjectManager()->CreateObject<StageBlock>(
    //                "Resource/Stage.png",
    //                VGet(posX, posY, 0.0f)
    //            );
    //        }
    //    }
    //}
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

void GameScene::Finalize()
{
    // 終了処理
}