#include "Texture.h"

#include <DxLib.h>

// -- 画像ロード時に使用 -- //
#include "Master.h"
#include "ResourceManager.h"

Texture::Texture(std::string filename, VECTOR centerPosition)
	:mvPosition(centerPosition)
{
	// -- 画像のロード -- //
	mnHandle = Master::mpResource->LoadGraphics(filename);

	// -- 画像のサイズ取得 -- //
	int size_x;
	int size_y;
	GetGraphSize(mnHandle, &size_x, &size_y);
	
	mfSizeX = static_cast<float>(size_x);
	mfSizeY = static_cast<float>(size_y);
}

Texture::~Texture()
{
	DeleteGraph(mnHandle);	// 読み込んだ画像の破棄
}

void Texture::Draw()
{
	VECTOR topLeft = CalculateTopLeftPosition();

	DrawGraph(
		static_cast<int>(topLeft.x),
		static_cast<int>(topLeft.y),
		mnHandle,
		TRUE
	);
}

// 中心座標を、DrawGraph用に左上座標に変換する
VECTOR Texture::CalculateTopLeftPosition()
{
	return VGet(
		mvPosition.x - (mfSizeX / 2.0f),
		mvPosition.y - (mfSizeY / 2.0f),
		mvPosition.z
	);
}