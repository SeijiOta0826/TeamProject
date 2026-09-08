#include "Gravity.h" // 追加
#include "Object2D.h"

Gravity::Gravity(Object2D* _owner)
	: mpOwner(_owner)
	, mbEnable(true)
	, mfGravity(9.8f)
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
	mpOwner = nullptr;
}

void Gravity::Update(float _deltaTime)
{
	if (!mbEnable || mpOwner == nullptr)
	{
		return;
	}

	// 重力加速度によって落下速度を計算
	mfVelocityY += mfGravity * _deltaTime;

	// 現在位置を取得
	VECTOR position = mpOwner->GetPosition();

	// 重力による移動量を計算
	float moveAmount = mfVelocityY * _deltaTime;

	// 2D座標ではYが下方向なので加算
	position.y += moveAmount;

	// y = 0 を地面として、それより下に行かないようにする
	if (position.y >= 790.0f)
	{
		position.y = 790.0f;
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