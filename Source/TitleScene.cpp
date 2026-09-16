#include "TitleScene.h"
#include "InputManager.h"
#include "DxLib.h"

#include "Master.h"
#include "SceneManager.h"

void TitleScene::Initialize()
{
	// シーンに入った瞬間のマウス状態を記録
	mbPreviousMouseLeft = (GetMouseInput() & MOUSE_INPUT_LEFT) != 0;
}

void TitleScene::Update(float _deltaTime)
{
	int mouseX;
	int mouseY;

	GetMousePoint(&mouseX, &mouseY);

	const int startX = 500;
	const int startY = 380;
	const int startWidth = 280;
	const int startHeight = 70;

	// STARTボタンの上にマウスがあるか
	mbStartSelected =
		mouseX >= startX &&
		mouseX <= startX + startWidth &&
		mouseY >= startY &&
		mouseY <= startY + startHeight;

	// 現在マウス左クリックが押されているか
	bool currentMouseLeft =
		(GetMouseInput() & MOUSE_INPUT_LEFT) != 0;

	// 「押した瞬間」だけ判定
	bool mouseLeftDown =
		currentMouseLeft && !mbPreviousMouseLeft;

	if (mbStartSelected && mouseLeftDown)
	{
		Master::mpSceneManager->SetNextScene(
			SCENE_TYPE::STAGE_SELECT_SCENE
		);
	}

	// 前フレームの状態を保存
	mbPreviousMouseLeft = currentMouseLeft;
}

void TitleScene::Draw()
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
		500,
		250,
		"AAAAAA",
		GetColor(0, 0, 0)
	);

	// スタート
	const int startX = 500;
	const int startY = 380;
	const int startWidth = 280;
	const int startHeight = 70;

	int buttonColor;

	if (mbStartSelected)
	{
		buttonColor = GetColor(255, 220, 100);
	}
	else
	{
		buttonColor = GetColor(200, 200, 200);
	}

	DrawBox(
		startX,
		startY,
		startX + startWidth,
		startY + startHeight,
		buttonColor,
		TRUE
	);

	DrawBox(
		startX,
		startY,
		startX + startWidth,
		startY + startHeight,
		GetColor(0, 0, 0),
		FALSE
	);

	DrawString(
		startX + 100,
		startY + 25,
		"START",
		GetColor(0, 0, 0)
	);
}

void TitleScene::Finalize()
{
	// 終了処理
}