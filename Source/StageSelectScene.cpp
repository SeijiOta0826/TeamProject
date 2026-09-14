#include "StageSelectScene.h"
#include "Master.h"
#include "SceneManager.h"
#include "DxLib.h"

void StageSelectScene::Initialize()
{
	// 初期化処理
}

void StageSelectScene::Update(float _deltaTime)
{
	int mouseX;
	int mouseY;

	GetMousePoint(&mouseX, &mouseY);

	const int buttonWidth = 280;
	const int buttonHeight = 70;
	const int startX = 500;
	const int startY = 220;
	const int interval = 100;

	// マウスがどのステージに乗っているか調べる
	for (int i = 0; i < 3; i++)
	{
		int left = startX;
		int top = startY + i * interval;
		int right = startX + buttonWidth;
		int bottom = top + buttonHeight;

		if (mouseX >= left &&
			mouseX <= right &&
			mouseY >= top &&
			mouseY <= bottom)
		{
			mnSelectedStage = i;
		}
	}

	// 左クリックで決定
	if (GetMouseInput() & MOUSE_INPUT_LEFT)
	{
		Master::mpSceneManager->SetStageNumber(mnSelectedStage + 1);

		Master::mpSceneManager->SetNextScene(SCENE_TYPE::GAME_SCENE);
	}
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

	// タイトル
	DrawString(
		500, 100,
		"ステージ選択",
		GetColor(0, 0, 0)
	);

	const int buttonWidth = 280;
	const int buttonHeight = 70;
	const int startX = 500;
	const int startY = 220;
	const int interval = 100;

	for (int i = 0; i < 3; i++)
	{
		int left = startX;
		int top = startY + i * interval;
		int right = left + buttonWidth;
		int bottom = top + buttonHeight;

		int color;

		if (mnSelectedStage == i)
		{
			// 選択中
			color = GetColor(255, 220, 100);
		}
		else
		{
			// 通常
			color = GetColor(200, 200, 200);
		}

		DrawBox(
			left,
			top,
			right,
			bottom,
			color,
			TRUE
		);

		DrawBox(
			left,
			top,
			right,
			bottom,
			GetColor(0, 0, 0),
			FALSE
		);

		char stageName[32];
		sprintf_s(
			stageName,
			"パターン%d",
			i + 1
		);

		DrawString(
			left + 90,
			top + 25,
			stageName,
			GetColor(0, 0, 0)
		);
	}
}

void StageSelectScene::Finalize()
{
	// 終了処理
}