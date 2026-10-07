#pragma once

class FakePlayer;

class FakePlayerController
{
public:
	FakePlayerController() = default;
	~FakePlayerController() = default;

	void Initialize(FakePlayer* _fakePlayer);	// 初期処理(主にFakePlayer設定)
	void Update();

	void UpdateMove();
	void UpdateOperationChange();
	void UpdateRotation();

private:
	FakePlayer* mpFakePlayer = nullptr;
};