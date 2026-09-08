#pragma once

#include <string>
#include <DxLib.h>
#include <vector>
#include <variant>

#include "Object2D.h"

class CollisionManager;

class Collider
{
public:
	Collider(Object2D* _obj);
	 ~Collider() = default;

	 void Initialize();	// 初期処理
	 void Finalize();	// 終了処理

	// -- Objの位置(Transform)からの相対オフセット位置アクセサ -- //
	void SetOffset(const VECTOR& _offset) { mvOffSetPos = _offset; }
	const VECTOR& GetOffset() const { return mvOffSetPos; }

	const VECTOR& GetHalfSize() const { return mvHalfSize; }
	void SetHalfSize(const VECTOR& _halfSize) { mvHalfSize = _halfSize; }

	VECTOR GetWorldPosition() const;	// Collider中心座標(Transform + Offset)を返す

	bool IsColliding() const;				// 何かしらに当たったら反応
	bool IsColliding(Tag _tag) const;		// 指定タグのColliderに衝突時、反応
	Object2D* GetCollision(Tag _tag) const;	// 指定タグの衝突したGameObjectを返す

	// -- 有効フラグのアクセサ -- //
	bool IsEnabled() const { return mbEnabled; }
	void SetEnabled(bool _enabled) { mbEnabled = _enabled; }

	// -- 付与先Object2Dの取得 -- //
	Object2D* GetObject2D() { return mpObj; }

private:
	friend class CollisionManager;

	void AddCollision(Collider* _collider) { mCollisions.push_back(_collider); }
	void ClearCollisions() { mCollisions.clear(); }

private:
	Object2D* mpObj = nullptr;

	VECTOR mvOffSetPos = VGet(0.0f, 0.0f, 0.0f);	// Objの位置(Transform)からの相対オフセット位置
	VECTOR mvHalfSize = VGet(0.5f, 0.5f, 0.0f);

	std::vector<Collider*> mCollisions;	// 指定フレームで衝突している他Colliderのコンテナ
	
	bool mbEnabled = true;	// 有効を示すフラグ
};