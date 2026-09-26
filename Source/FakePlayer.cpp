#include "FakePlayer.h"

// -- Module -- //
#include "Transform.h"
#include "Graphic.h"
#include "Collider.h"
#include "Gravity.h"

#include "GameConfig.h"

void FakePlayer::InitComponent()
{
	// -- Module追加 -- //
	AddModule<Transform>();
	AddModule<Graphic>(GetModelFilename());
	AddModule<Collider>();
	AddModule<Gravity>();

	// -- 衝突判定を取得するObjを指定 -- //
	auto collider = GetModule<Collider>();
	collider->AddCollisionTag(Tag::BLOCK);
	collider->SetHalfSize(VGet(GameConfig::CELL_SIZE / 2.0f, GameConfig::CELL_SIZE / 2.0f, 0.0f));
}

void FakePlayer::Update(float _deltaTime)
{
	GameObject::Update(_deltaTime);
}

void FakePlayer::Draw()
{
	GameObject::Draw();
}