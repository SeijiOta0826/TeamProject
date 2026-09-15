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
#include "Goal.h"


void GameScene::Initialize()
{
	mbPreviousMouseLeft = (GetMouseInput() & MOUSE_INPUT_LEFT) != 0;

    // 初期化処理
	mpPlayer =
		this
		->GetObjectManager()
		->CreateObject<Player>(
			"Resource/Player.png",
			VGet(120.0f, 500.0f, 0.0f)
		);

	// ゴール画像 できたら誰か変えといて
	this
		->GetObjectManager()
		->CreateObject<Goal>(
			"Resource/Help.png",
			VGet(1100.0f, 500.0f, 0.0f)
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
	if (mbIsClear)
	{
		UpdateClear();
		return;
	}

	// 更新処理
	Scene::Update(deltaTime);

	if (mpPlayer != nullptr &&
		mpPlayer->IsGoalReached())
	{
		mbIsClear = true;
	}
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

    if (mbIsPaused)
    {
        DrawPause();
    }

	if (mbIsClear)
	{
		DrawClear();
	}
}

void GameScene::DrawPause()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);

	DrawBox(
		0, 0,
		1280, 720,
		GetColor(0, 0, 0),
		TRUE
	);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	DrawString(
		570,
		200,
		"PAUSE",
		GetColor(255, 255, 255)
	);

	// 再開ボタン
	DrawBox(
		500, 300,
		780, 370,
		GetColor(200, 200, 200),
		TRUE
	);

	DrawBox(
		500, 300,
		780, 370,
		GetColor(255, 255, 255),
		FALSE
	);

	DrawString(
		625, 
		325,
		"再開",
		GetColor(0, 0, 0)
	);

	// ステージ選択へ戻るボタン
	DrawBox(
		500, 400,
		780, 470,
		GetColor(200, 200, 200),
		TRUE
	);

	DrawBox(
		500, 400,
		780, 470,
		GetColor(255, 255, 255),
		FALSE
	);

	DrawString(
		560,
		425,
		"ステージ選択へ戻る",
		GetColor(0, 0, 0)
	);

	// タイトルへ戻るボタン
	DrawBox(
		500, 500,
		780, 570,
		GetColor(200, 200, 200),
		TRUE
	);

	DrawBox(
		500, 500,
		780, 570,
		GetColor(255, 255, 255),
		FALSE
	);

	DrawString(
		583,
		525,
		"タイトルへ戻る",
		GetColor(0, 0, 0)
	);
}

void GameScene::DrawClear()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);

	DrawBox(
		0, 0,
		1280, 720,
		GetColor(0, 0, 0),
		TRUE
	);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	DrawString(
		570, 250,
		"CLEAR!",
		GetColor(255, 255, 255)
	);

	DrawString(
		500, 350,
		"ステージクリア！",
		GetColor(255, 255, 255)
	);

	// ステージ選択へ戻るボタン
	DrawBox(
		500, 400,
		780, 470,
		GetColor(80, 80, 80),
		TRUE
	);

	DrawBox(
		500, 400,
		780, 470,
		GetColor(255, 255, 255),
		FALSE
	);

	DrawString(
		570, 425,
		"ステージ選択へ戻る",
		GetColor(255, 255, 255)
	);
}

void GameScene::UpdateClear()
{
	int mouseX;
	int mouseY;

	GetMousePoint(&mouseX, &mouseY);

	bool currentMouseLeft =
		(GetMouseInput() & MOUSE_INPUT_LEFT) != 0;

	bool mouseLeftDown =
		currentMouseLeft && !mbPreviousMouseLeft;

	if (mouseLeftDown &&
		mouseX >= 500 && mouseX <= 780 &&
		mouseY >= 400 && mouseY <= 470)
	{
		Master::mpSceneManager->SetNextScene(
			SCENE_TYPE::STAGE_SELECT_SCENE
		);
	}

	mbPreviousMouseLeft = currentMouseLeft;
}

void GameScene::UpdatePause()
{
	bool currentP = CheckHitKey(KEY_INPUT_P) != 0;

	if (currentP && !mbPreviousP)
	{
		mbIsPaused = !mbIsPaused;
	}

	mbPreviousP = currentP;

	if (!mbIsPaused)
	{
		return;
	}

	// マウス座標
	int mouseX;
	int mouseY;

	GetMousePoint(&mouseX, &mouseY);

	// 左クリック

	bool currentMouseLeft = (GetMouseInput() & MOUSE_INPUT_LEFT) != 0;

	bool mouseLeftDown = currentMouseLeft && !mbPreviousMouseLeft;

	// 再開ボタン
	if (mouseLeftDown &&
		mouseX >= 500 && mouseX <= 780 &&
		mouseY >= 300 && mouseY <= 370)
	{
		mbIsPaused = false;
	}

	// ステージ選択へ戻るボタン
	if (mouseLeftDown &&
		mouseX >= 500 && mouseX <= 780 &&
		mouseY >= 400 && mouseY <= 470)
	{
		Master::mpSceneManager->SetNextScene(
			SCENE_TYPE::STAGE_SELECT_SCENE
		);
	}

	// タイトルへ戻る
	if (mouseLeftDown &&
		mouseX >= 500 && mouseX <= 780 &&
		mouseY >= 500 && mouseY <= 570)
	{
		Master::mpSceneManager->SetNextScene(
			SCENE_TYPE::TITLE_SCENE
		);
	}

	mbPreviousMouseLeft = currentMouseLeft;
}

void GameScene::SetStageNumber(int _stageNumber)
{
    mnStageNumber = _stageNumber;
}

void GameScene::Finalize()
{
    // 終了処理
}