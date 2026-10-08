#pragma once
#include "GameObject.h"

#include "FakePlayerController.h"

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

	void Move(VECTOR _direction);					// 移動処理
	void Rotation(float _rotateDirection);
protected:
	const char* GetModelFilename() const override
	{
		return "Resource/Obj/test_player.png";
	}

private:
	FakePlayerController mController;	// コントローラー

	float mfSpeed = 10.0f;
	float mfRotationPower = 5.0f;	// 回転力(単位は度数)

	VECTOR mvCollisionCorrection = VGet(0.0f, 0.0f, 0.0f);
};