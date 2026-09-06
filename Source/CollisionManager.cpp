#include "CollisionManager.h"

#include "Collider.h"
#include "Object2D.h"

#include <DxLib.h>	// デバッグ表示のカラー指定のため使用
#include <cmath>
#include <algorithm>

void CollisionManager::Finalize() {
	for (auto* collider : mColliders){
		collider->ClearCollisions();
	}

	mColliders.clear();
}

void CollisionManager::Update() {
	// 前フレームの衝突結果をリセット
	for (auto* collider : mColliders) {
		collider->ClearCollisions();
	}

	// 判定を行うColliderを選び、衝突結果を各自処理するコンテナに登録
	for (size_t i = 0;
		i < mColliders.size();
		++i) {
		Collider* a = mColliders[i];
		
		if (!a->IsEnabled()) continue;

		for (size_t j = i + 1;
			j < mColliders.size();
			++j) {
			Collider* b = mColliders[j];

			if (!b->IsEnabled()) continue;

			if (CheckBoxBox(a, b)) {
				a->AddCollision(b);
				b->AddCollision(a);
			}
		}
	}
}

void CollisionManager::Register(
	Collider* _collider
) {
	if (_collider == nullptr) return;

	for (auto* collider : mColliders) {
		if (collider == _collider) return;
	}

	mColliders.push_back(_collider);
}

void CollisionManager::Unregister(
	Collider* _collider
) {
	for (auto collider = mColliders.begin();
		collider != mColliders.end();
		++collider) {
		if (*collider == _collider) {
			mColliders.erase(collider);
			return;
		}
	}
}

bool CollisionManager::CheckBoxBox(
	Collider* _boxA,
	Collider* _boxB
) const {
	const VECTOR posA =
		_boxA->GetWorldPosition();

	const VECTOR posB =
		_boxB->GetWorldPosition();

	const VECTOR halfA =
		_boxA->GetHalfSize();

	const VECTOR halfB =
		_boxB->GetHalfSize();

	const VECTOR minA =
		VSub(posA, halfA);

	const VECTOR maxA =
		VAdd(posA, halfA);

	const VECTOR minB =
		VSub(posB, halfB);

	const VECTOR maxB =
		VAdd(posB, halfB);

	if (maxA.x < minB.x ||
		minA.x > maxB.x)
	{
		return false;
	}

	if (maxA.y < minB.y ||
		minA.y > maxB.y)
	{
		return false;
	}

	if (maxA.z < minB.z ||
		minA.z > maxB.z)
	{
		return false;
	}

	return true;
}

bool CollisionManager::GetBoxBoxCollision(
	Collider* _a,
	Collider* _b,
	CollisionInfo& _info
) const
{
	if (_a == nullptr || _b == nullptr) 
		return false;

	const VECTOR posA = _a->GetWorldPosition();
	const VECTOR posB = _b->GetWorldPosition();

	const VECTOR halfA = _a->GetHalfSize();
	const VECTOR halfB = _b->GetHalfSize();

	const float overlapX =
		(halfA.x + halfB.x) -
		std::abs(posA.x - posB.x);

	const float overlapY =
		(halfA.y + halfB.y) -
		std::abs(posA.y - posB.y);

	const float overlapZ =
		(halfA.z + halfB.z) -
		std::abs(posA.z - posB.z);

	// そもそも衝突していない
	if (overlapX <= 0.0f ||
		overlapY <= 0.0f ||
		overlapZ <= 0.0f)
	{
		return false;
	}

	// 一番めり込みが浅い軸を選択
	_info.penetration = overlapX;
	_info.normal = VGet(
		posA.x < posB.x ? -1.0f : 1.0f,
		0.0f,
		0.0f
	);

	if (overlapY < _info.penetration)
	{
		_info.penetration = overlapY;

		_info.normal = VGet(
			0.0f,
			posA.y < posB.y ? -1.0f : 1.0f,
			0.0f
		);
	}

	if (overlapZ < _info.penetration)
	{
		_info.penetration = overlapZ;

		_info.normal = VGet(
			0.0f,
			0.0f,
			posA.z < posB.z ? -1.0f : 1.0f
		);
	}

	return true;
}