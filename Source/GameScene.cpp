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

#include "FontManager.h"



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

	// フォントの取得
	mFontHandle = Master::mpFontManager->GetFont("メイリオ", 24, 1, DX_FONTTYPE_ANTIALIASING);
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

	//文字描画(テスト)
    DrawStringToHandle(
        10, 10,
        "BLOCK ブロック TEST",
        GetColor(255, 255, 255),
        mFontHandle
	);


    Debug::Draw();
    Scene::Draw();
}

void GameScene::Finalize()
{
    // 終了処理
}