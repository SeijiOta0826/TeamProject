#include "StageSelectScene.h"
#include "Master.h"
#include "SceneManager.h"
#include "DxLib.h"
#include "InputManager.h"

void StageSelectScene::Initialize()
{
	mbPreviousMouseLeft =
		(GetMouseInput() & MOUSE_INPUT_LEFT) != 0;
}

void StageSelectScene::Update(float _deltaTime)
{
	int mouseX;
	int mouseY;

	GetMousePoint(&mouseX, &mouseY);

	// ステージボタン設定
	const int buttonWidth = 300;
	const int buttonHeight = 100;

	const int startX = 340;
	const int startY = 220;

	const int horizontalInterval = 320;
	const int verticalInterval = 130;

	// マウスがどのステージボタンの上にあるか
	for (int i = 0; i < 6; i++)
	{
		int column = i % 2;
		int row = i / 2;

		int left =
			startX + column * horizontalInterval;

		int top =
			startY + row * verticalInterval;

		int right = left + buttonWidth;
		int bottom = top + buttonHeight;

		if (mouseX >= left &&
			mouseX <= right &&
			mouseY >= top &&
			mouseY <= bottom)
		{
			mnSelectedStage = i;
		}
	}

	// 左クリックが「押された瞬間」だけ判定
	bool currentMouseLeft =
		(GetMouseInput() & MOUSE_INPUT_LEFT) != 0;

	bool mouseLeftDown =
		currentMouseLeft && !mbPreviousMouseLeft;

	if (mouseLeftDown)
	{
		// ステージ番号を設定
		Master::mpSceneManager->SetStageNumber(
			mnSelectedStage + 1
		);

		// ゲーム画面へ
		Master::mpSceneManager->SetNextScene(
			SCENE_TYPE::GAME_SCENE
		);
	}

	// 前フレームのクリック状態を保存
	mbPreviousMouseLeft = currentMouseLeft;
}

void StageSelectScene::Draw()
{
	// 背景

	DrawBox(
		0, 0,
		1280, 720,
		GetColor(217, 198, 143),
		TRUE
	);

	// 背景の上側に帯
	DrawBox(
		0, 0,
		1280, 180,
		GetColor(190, 170, 115),
		TRUE
	);

	// タイトル

	DrawString(
		520,
		55,
		"STAGE SELECT",
		GetColor(255, 255, 255)
	);

	DrawString(
		545,
		110,
		"ステージを選択してください",
		GetColor(0, 0, 0)
	);

	// ステージボタン

	const int buttonWidth = 300;
	const int buttonHeight = 100;

	const int startX = 340;
	const int startY = 220;

	const int horizontalInterval = 320;
	const int verticalInterval = 130;

	for (int i = 0; i < 6; i++)
	{
		int column = i % 2;
		int row = i / 2;

		int left =
			startX + column * horizontalInterval;

		int top =
			startY + row * verticalInterval;

		int right = left + buttonWidth;
		int bottom = top + buttonHeight;

		// 選択状態によって色を変更
		int color;

		if (mnSelectedStage == i)
		{
			// 選択中
			color = GetColor(255, 220, 100);
		}
		else
		{
			// 通常
			color = GetColor(235, 225, 190);
		}

		// ボタン本体
		DrawBox(
			left,
			top,
			right,
			bottom,
			color,
			TRUE
		);

		// 外枠
		DrawBox(
			left,
			top,
			right,
			bottom,
			GetColor(60, 50, 35),
			FALSE
		);

		// ステージ番号
		char stageNumber[32];

		sprintf_s(
			stageNumber,
			"STAGE %d",
			i + 1
		);

		DrawString(
			left + 25,
			top + 22,
			stageNumber,
			GetColor(80, 65, 40)
		);

		// パターン名
		char stageName[32];

		sprintf_s(
			stageName,
			"パターン%d",
			i + 1
		);

		DrawString(
			left + 25,
			top + 55,
			stageName,
			GetColor(0, 0, 0)
		);
	}

	// 下部説明

	DrawString(
		480,
		640,
		"マウスでステージを選択",
		GetColor(80, 70, 50)
	);
}

void StageSelectScene::Finalize()
{
	// 終了処理
}