#pragma once
#include "GameObject.h"

class FakePlayer : public GameObject
{
public:
	FakePlayer() = default;
	~FakePlayer() = default;

	void Init() override;
	void InitComponent() override;
	void Finalize() override;
	void Update(float _deltaTime) override;
	void Draw() override;

	//void ResolveStageCollision();	// ステージブロックとの衝突解決処理
	void ResolveCollision() override;
private:
	void Move();					// 移動処理

protected:
	const char* GetModelFilename() const override
	{
		return "Resource/Obj/test_player.png";
	}

private:
	float mfSpeed = 10.0f;

	VECTOR mvCollisionCorrection = VGet(0.0f, 0.0f, 0.0f);
};