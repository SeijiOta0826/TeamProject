#include "DxLib.h"

#include "ScreenConfig.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	// -- 初期設定 -- //
	ChangeWindowMode(true);
	SetGraphMode(
		ScreenConfig::SCREEN_WIDTH,
		ScreenConfig::SCREEN_HEIGHT,
		0
	);

	// -- DXLib初期化 -- //
	if (DxLib_Init() == -1) 
	{
		return -1;
	}

	//Todo:	初期化処理系をここへ


	SetDrawScreen(DX_SCREEN_BACK);

	// -- 3D描画設定 -- //
	SetUseZBufferFlag(true);
	SetWriteZBufferFlag(true);

	SetLightDifColor(GetColorF(1.0f, 0.8f, 0.4f, 0.0f)); 	
	SetLightAmbColor(GetColorF(3.2f, 3.2f, 3.2f, 0.0f));

	// メインループ
	int prevTime = GetNowCount();

	while (ProcessMessage() == 0
	&& CheckHitKey(KEY_INPUT_ESCAPE) == 0) 
	{
		SetUseLighting(TRUE);  

		int currentTime = GetNowCount();	
		float deltaTime = (currentTime - prevTime) / 1000.0f;	
		prevTime = currentTime;

		// -- 更新処理 -- //
		//Todo:	更新処理をここへ



		// -- 描画処理 -- //
		ClearDrawScreen();

		//Todo:	描画処理をここへ


		ScreenFlip();


		// -- フレームレート設定 -- //
		while (GetNowCount() - currentTime < 17)
		{
			//60fpsに調整
		}

		// Todo : Scene変更のチェッカーをここへ

	}

	// -- 終了処理　-- // 
	// 終了処理をここへ


	DxLib_End();	// DXライブラリ使用の終了
	return 0;	//ソフトの終了
}