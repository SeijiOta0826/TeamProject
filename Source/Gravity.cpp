#include "Gravity.h" // 追加
#include "GameObject.h"

#include "ScreenConfig.h"
#include "GameConfig.h"

Gravity::Gravity(GameObject* _owner)
	: mpOwner(_owner)
	, mbEnable(true)
	, mfGravity(GameConfig::GLAVITY)
	, mfVelocityY(0.0f)
{

}

Gravity::~Gravity()
{
	Finalize();
}

void Gravity::Initialize()
{
	mfVelocityY = 0.0f;
	mbEnable = true;
}

void Gravity::Finalize()
{
	// -- 所有するポインタの解放 -- //
	delete mpOwner;
	mpOwner = nullptr;
}

void Gravity::Update(float _deltaTime)
{
	if (!mbEnable || mpOwner == nullptr)
	{
		return;
	}

	if (mpOwner->IsGrounded())
	{
		ResetVerticalVelocity();
		return;
	}

	// 重力加速度によって落下速度を計算
	mfVelocityY += mfGravity * _deltaTime;

	// 現在位置を取得
	VECTOR position = mpOwner->GetPosition();

	// 重力による移動量を計算
		// ota : ここdeltaTimeいるんか。僕は💩です
	float moveAmount = mfVelocityY * _deltaTime;

	// 2D座標ではYが下方向なので加算
	position.y += moveAmount;

	// y = 0 を地面として、それより下に行かないようにする
		// ota : マジックナンバーを直させていただきます。僕は💩です
	if (position.y >= ScreenConfig::SCREEN_HEIGHT)
	{
		position.y = ScreenConfig::SCREEN_HEIGHT;
		mfVelocityY = 0.0f;
	}

	// Objに座標を反映
	mpOwner->SetPosition(position);
}

void Gravity::SetEnable(bool _enable)
{
	mbEnable = _enable;

	if (!mbEnable)
	{
		mfVelocityY = 0.0f;
	}
}

bool Gravity::IsEnable() const
{
	return mbEnable;
}

void Gravity::ResetVerticalVelocity()
{
	mfVelocityY = 0.0f;
}