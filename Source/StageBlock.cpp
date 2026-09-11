#include "StageBlock.h"

#include "Gravity.h"

StageBlock::StageBlock(std::string filename, VECTOR initPos)
	:GameObject(filename, initPos)
{
	SetTag(Tag::BLOCK);
	mpGravity->SetEnable(false);
}

void StageBlock::Update(float _deltaTime)
{
	GameObject::Update(_deltaTime);
}

void StageBlock::Draw()
{
	GameObject::Draw();
}