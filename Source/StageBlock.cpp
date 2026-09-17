#include "StageBlock.h"

// #include "Gravity.h"
#include "Transform.h"
#include "Graphic.h"
#include "Collider.h"

void StageBlock::Init()
{
	// -- タグ設定 -- //
	SetTag(Tag::BLOCK);
}

void StageBlock::InitComponent()
{
	// -- Module追加 -- //
	AddModule<Transform>();
	AddModule<Graphic>(GetModelFilename());
	AddModule<Collider>();

	// -- 衝突判定を取得するObjを指定 -- //
	auto collider = GetModule<Collider>();
	collider->AddCollisionTag(Tag::PLAYER_CELL);
}

void StageBlock::Update(float _deltaTime)
{
	GameObject::Update(_deltaTime);
}

void StageBlock::Draw()
{
	GameObject::Draw();
}