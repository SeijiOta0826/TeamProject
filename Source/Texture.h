#pragma once
#include <string>
#include "DxLib.h"

// memo : 画像の描画を担当するクラス
class Texture
{
public:
	Texture(std::string filename, VECTOR centerPosition);
	~Texture();

	void Draw();

	void DrawAt(VECTOR centerPosition);
	
	// -- 座標アクセサ -- //
	void SetPosition(VECTOR centerPosition){ mvPosition = centerPosition; }
	VECTOR GetPosition() { return mvPosition; }
	
	// -- サイズ設定 -- //
	void SetSize(VECTOR _settingSize) { mvSize = _settingSize; }

	float GetSizeX() { return mfSizeX; }
	float GetSizeY() { return mfSizeY; }

	// -- ハンドル取得 -- //
	int GetHandle() { return mnHandle; }

private:
	VECTOR CalculateTopLeftPosition();	// 中心座標を、DrawGraph用に左上座標に変換する

private:
	int mnHandle = -1;		// 読み込んだ画像のハンドル

	VECTOR mvPosition;			// 描画画像の中心座標
	VECTOR mvSize;				// 画像の大きさ
	float mfSizeX = 1.0f;		// 画像の幅
	float mfSizeY = 1.0f;		// 画像の高さ

};
