#pragma once
#include <DxLib.h>	// VECTOR用
#include <vector>

class Collider;

struct CollisionInfo
{
	VECTOR normal;				// 押し出す方向
	float penetration = 0.0f;	// どれだけめり込んでいるか
};

/* memo : 
* 各Objが持つ、「Colliderクラス」を総括して管理するクラス。
* 主に毎フレーム全Collider同士の衝突判定を行い、
*	各Colliderへ「衝突しているCollider」のデータを渡す。
* 
* 所有権はScene。
* 
* 9/8時点では当たり判定は「Box型」のみ
*/

class CollisionManager
{
public:
	CollisionManager() = default;
	~CollisionManager() = default;

	// void Initialize();
	void Finalize();

	void Register(Collider* _collider);			// 呼び出し先のColliderをManagerに登録
	void Unregister(Collider* _collider);		// 呼び出し先のColliderをManagerから除外

	void Update();	// 全Collider同士の判定

	// void DrawDebag() const;	

	// Box対Boxのめり込み具合と方向を取得する(infoに)
	bool GetBoxBoxCollision(
		Collider* _a,
		Collider* _b,
		CollisionInfo& _info
	) const;

private:
	bool CheckBoxBox(Collider* _boxA, Collider* _boxB) const;	// Box対Boxが衝突を取得する

private:
	std::vector<Collider*> mColliders;	// 使用されている当たり判定データのコンテナ
};