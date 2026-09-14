#include "Player_test.h"

#include "PlayerPiece.h"

#include "Master.h"
#include "SceneManager.h"
#include "Scene.h"
#include "ObjectManager.h"
#include "InputManager.h"

#include "GameConfig.h"

Player_test::Player_test()
{
	for (int column = 0;
		column < SIZE;
		column++)
	{
		for (int row = 0;
			row < SIZE;
			row++)
		{
			// -- Playerに基づく相対座標を取得 -- //
			VECTOR offset = VGet(0.0f, 0.0f, 0.0f);

			offset.x =
				(row - 1) * GameConfig::CELL_SIZE;

			offset.y =
				(column - 1) * GameConfig::CELL_SIZE;

			// -- Playerが保有するPieceの生成 & 初期設定-- //
			mPieces[row][column] =
				Master::mpSceneManager
				->GetCurrentScene()
				->GetObjectManager()
				->CreateObject<PlayerPiece>(
					this,
					"Resource/Player.png",
					VAdd(
						mvPosition,
						offset
					)
				);

			mPieces[row][column]
				->SetLocalPosition(
					offset
				);
		}
	}
}

Player_test::~Player_test()
{

}

void Player_test::Update()
{
	// Eキーを押したら変形モードに入る
	if (InputManager::GetInstance().GetButtonDown(Button::Transform))
	{
		mbIsTransforming = true;
	}

	// 変形中かどうかで入力を切り替える
	if (mbIsTransforming)
	{
		UpdateTransformUI();
		return; //変形中は移動や重力処理を行わない
	}

	Move();
	UpdateTransformCollider();
}

void Player_test::Draw()
{
	// 変形画面
	if (mbIsTransforming)
	{
		DrawTransformUI();
	}
	UpdateTransformUI();
}

void Player_test::Move()
{
	VECTOR inputDirection = VGet(0.0f, 0.0f, 0.0f);

	inputDirection.x += InputManager::GetInstance().GetAxis(Axis::MoveX);
	inputDirection.y += InputManager::GetInstance().GetAxis(Axis::MoveY);

	if (VSize(inputDirection) == 0.0f)
		return;

	VECTOR moveAmount = VScale(inputDirection, mfSpeed);

	VECTOR nextPos = VAdd(
		GetPosition(),
		moveAmount
	);

	SetPosition(nextPos);
}

void Player_test::UpdateTransformCollider()
{
	for (int y = 0;
		y < SIZE;
		y++)
	{
		for (int x = 0;
			x < SIZE;
			x++)
		{
			bool enabled = mShape[x][y];

			mPieces[x][y]->SetEnabled(enabled);
		}
	}
}

void Player_test::DrawTransformUI()
{
	int screenWidth;
	int screenHeight;

	GetDrawScreenSize(&screenWidth, &screenHeight);

	const int cellSize = 100;
	const int gridSize = cellSize * 3;

	const int startX = (screenWidth - gridSize) / 2;
	const int startY = (screenHeight - gridSize) / 2;

	// 背景
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);

	DrawBox(
		0,
		0,
		screenWidth,
		screenHeight,
		GetColor(0, 0, 0),
		TRUE
	);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// 3×3
	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			int left = startX + x * cellSize;
			int top = startY + y * cellSize;
			int right = left + cellSize;
			int bottom = top + cellSize;

			int color;

			if (mShape[y][x])
			{
				// ON
				color = GetColor(255, 255, 255);
			}
			else
			{
				// OFF
				color = GetColor(80, 80, 80);
			}

			DrawBox(
				left,
				top,
				right,
				bottom,
				color,
				TRUE
			);

			// 枠
			DrawBox(
				left,
				top,
				right,
				bottom,
				GetColor(255, 255, 255),
				FALSE
			);
		}
	}

	DrawString(
		startX,
		startY - 40,
		"変形",
		GetColor(255, 255, 255)
	);
}

void Player_test::UpdateTransformUI()
{
	int mouseX = InputManager::GetInstance().GetMouse().GetX();
	int mouseY = InputManager::GetInstance().GetMouse().GetY();

	const int cellSize = 100;
	const int gridSize = cellSize * 3;

	int screenWidth;
	int screenHeight;

	GetDrawScreenSize(&screenWidth, &screenHeight);

	const int startX = (screenWidth - gridSize) / 2;
	const int startY = (screenHeight - gridSize) / 2;

	// マウスが3×3の範囲内にあるか
	if (mouseX >= startX &&
		mouseX < startX + gridSize &&
		mouseY >= startY &&
		mouseY < startY + gridSize)
	{
		// 何列目・何行目をクリックしたか計算
		int cellX = (mouseX - startX) / cellSize;
		int cellY = (mouseY - startY) / cellSize;

		// 左クリックされたらON/OFF切り替え
		if (InputManager::GetInstance().GetMouse().IsDown(MOUSE_INPUT_LEFT))
		{
			mShape[cellY][cellX] = !mShape[cellY][cellX];
		}
	}

	// Enterで変形を確定
	if (InputManager::GetInstance().GetButtonDown(Button::Confirm))
	{
		UpdateTransformCollider();

		// 変形によって大きくなった場合のめり込み防止
		VECTOR position = GetPosition();
		position.y -= 10.0f;
		SetPosition(position);

		mbIsTransforming = false;
	}
}
