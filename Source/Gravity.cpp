#include "Gravity.h"

#include <DxLib.h>

#include "GameObject.h"
#include "Transform.h"

#include "ScreenConfig.h"
#include "GameConfig.h"

void Gravity::Update(float _deltaTime)
{
	if (mpGameObject->IsGrounded())
	{
		ResetVerticalVelocity();
		return;
	}

	// 重力加速度によって落下速度を計算
	mfVelocityY += GameConfig::GLAVITY * _deltaTime;

	// -- 座標を取得 -- //
	auto transform = mpGameObject->GetModule<Transform>();
	VECTOR position = transform->GetPosition();

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
	transform->SetPosition(position);
}

void Gravity::ResetVerticalVelocity()
{
	mfVelocityY = 0.0f;
}