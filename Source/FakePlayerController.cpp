#include "FakePlayerController.h"

#include "FakePlayer.h"

#include "InputManager.h"

#include <DxLib.h>	// VECTOR用

void FakePlayerController::Initialize(FakePlayer* _fakePlayer)
{
	mpFakePlayer = _fakePlayer;
}

void FakePlayerController::Update()
{
	// Todo : 各操作を関数化した処理を並べる
	UpdateMove();
	UpdateOperationChange();
	UpdateRotation();
}

void FakePlayerController::UpdateMove()
{
	// -- 入力値を取得 -- //
	VECTOR inputDirection = VGet(0.0f, 0.0f, 0.0f);

	inputDirection.x += InputManager::GetInstance().GetAxis(Axis::MoveX_FAKE);
	inputDirection.y += InputManager::GetInstance().GetAxis(Axis::MoveY_FAKE);

	if (VSize(inputDirection) == 0.0f)
		return;

	// -- 入力(移動方向)をFakePlayerに渡す -- //
	mpFakePlayer->Move(inputDirection);
}

void FakePlayerController::UpdateOperationChange()
{
	if (InputManager::GetInstance().GetButtonDown(Button::OperationChange_toPlayer))
		InputManager::GetInstance().SetInputMode(InputMode::Normal);
}

void FakePlayerController::UpdateRotation()
{
	float rotateDirection = InputManager::GetInstance().GetAxis(Axis::Rotation_FAKE);

	mpFakePlayer->Rotation(rotateDirection);
}