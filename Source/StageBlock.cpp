#include "StageBlock.h"

#include "Collider.h"

#include "Texture.h"
#include "GameConfig.h"

StageBlock::StageBlock(std::string filename, VECTOR initPos)
	:Object2D(filename, initPos)
{
	SetTag(Tag::BLOCK);
	mpTexture->SetSize(VGet(GameConfig::CELL_SIZE, GameConfig::CELL_SIZE, 0.0f));

	mpCollider = new Collider(this);
	mpCollider->Initialize();

	mpCollider->SetHalfSize(VGet(GameConfig::CELL_SIZE / 2, GameConfig::CELL_SIZE / 2, 0.0f));
}

void StageBlock::Update(float _deltaTime)
{

}

void StageBlock::Draw()
{
	Object2D::Draw();
}