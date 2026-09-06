#pragma once
#include <DxLib.h>	// VECTOR用
#include <vector>

class Collider;

struct CollisionInfo
{
	VECTOR normal;				// 押し出す方向
	float penetration = 0.0f;	// どれだけめり込んでいるか
};

class CollisionManager
{
public:
	CollisionManager() = default;
	~CollisionManager() = default;

	void Initialize();
	void Finalize();

	void Register(Collider* _collider);
	void Unregister(Collider* _collider);

	void Update();

	void DrawDebag() const;

	bool GetBoxBoxCollision(
		Collider* _a,
		Collider* _b,
		CollisionInfo& _info
	) const;

private:
	bool CheckBoxBox(Collider* _boxA, Collider* _boxB) const;

private:
	std::vector<Collider*> mColliders;	// 使用されている当たり判定データのコンテナ
};