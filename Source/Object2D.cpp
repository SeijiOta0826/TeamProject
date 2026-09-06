#include"Object2D.h"
#include"Texture.h"

Object2D::Object2D(std::string filename, VECTOR initPos)
	:mvPosition(initPos)
{
	mpTexture = new Texture(filename, initPos);
}

Object2D::~Object2D()
{
	delete mpTexture;
	mpTexture = nullptr;
}

void Object2D::Draw()
{
	if (mpTexture != nullptr)
	{
		mpTexture->Draw();
	}
}

void Object2D::SetPosition(VECTOR _pos)
{
	mvPosition = _pos;

	// -- テクスチャー(描画処理クラス)にも座標を反映する -- //
	if (mpTexture != nullptr)
	{
		mpTexture->SetPosition(mvPosition);
	}
}


