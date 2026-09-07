#include "Debag.h"

#include "ScreenConfig.h"
#include "GameConfig.h"

void Debag::Draw()
{
	if (!mbEnable)
		return;

	DrawGrid();
	DrawColliders();
	DrawGameTime();
	DrawTexts();

	mTexts.clear();
}

void Debag::DrawGrid()
{
	constexpr int GRID_SIZE =
		static_cast<int>(GameConfig::CELL_SIZE);

	const int screenWidth =
		static_cast<int>(ScreenConfig::SCREEN_WIDTH);

	const int screenHeight =
		static_cast<int>(ScreenConfig::SCREEN_HEIGHT);

	const int color =
		GetColor(100, 100, 100);

	// 縦線
	for (int x = 0; x <= screenWidth; x += GRID_SIZE)
	{
		DrawLine(
			x,
			0,
			x,
			screenHeight,
			color
		);
	}

	// 横線
	for (int y = 0; y <= screenHeight; y += GRID_SIZE)
	{
		DrawLine(
			0,
			y,
			screenWidth,
			y,
			color
		);
	}
}

void Debag::DrawColliders()
{
	// Collider描画
}

void Debag::DrawGameTime()
{
	// 経過時間描画
}

void Debag::DrawTexts()
{
	// Print()で登録された文字列を描画
	constexpr int START_X = 10;
	constexpr int START_Y = 10;
	constexpr int LINE_HEIGHT = 20;

	int y = START_Y;

	for (const auto& text : mTexts)
	{
		DrawString(
			START_X,
			y,
			text.c_str(),
			GetColor(255, 255, 255)
		);

		y += LINE_HEIGHT;
	}
}