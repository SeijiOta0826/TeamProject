#include "GameScene.h"

#include "Master.h"
#include "SceneManager.h"
#include "Scene.h"
#include "ObjectManager.h"

#include "Player.h"
#include "StageBlock.h"

void GameScene::Initialize()
{
    // 初期化処理
    auto player =
       this
        ->GetObjectManager()
        ->CreateObject<Player>(
            "Resource/Obj/test_player.png",
            VGet(0.0f, 0.0f, 0.0f)
        );

    auto block =
        this
        ->GetObjectManager()
        ->CreateObject<StageBlock>(
            "Resource/Obj/test_field.png",
            VGet(300.0f, 300.0f, 0.0f)
        );
}

void GameScene::Update(float deltaTime)
{
    // 更新処理
    Scene::Update(deltaTime);
}

void GameScene::Draw()
{
    Scene::Draw();
}

void GameScene::Finalize()
{
    // 終了処理
}