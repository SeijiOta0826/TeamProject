#include "StageBlock.h"

#include "Collider.h"

StageBlock::StageBlock(std::string filename, VECTOR initPos)
	:Object2D(filename, initPos)
{
	SetTag(Tag::BLOCK);

	mpCollider = new Collider(this);
	mpCollider->Initialize();

	mpCollider->SetHalfSize(VGet(50.0f, 50.0f, 0.0f));
}

void StageBlock::Update(float _deltaTime)
{

}

void StageBlock::Draw()
{
	Object2D::Draw();
}