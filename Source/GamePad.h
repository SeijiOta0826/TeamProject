#pragma once
#include <DxLib.h>

enum class PadAxis
{
	LeftX,
	LeftY,

	RightX,
	RightY,

	TriggerLeft,
	TriggerRight,
};

class GamePad
{
public:
	GamePad() = default;
	~GamePad() = default;

	void Update();

	bool IsConnected() const;

	bool IsPressed(int _button) const;
	bool IsDown(int _button) const;
	bool IsUp(int _button) const;

	VECTOR GetLeftStick() const;
	VECTOR GetRightStick() const;

private:
	int mNowState = 0;
	int mOldState = 0;

	VECTOR mLeftStick;
	VECTOR mRightStick;

	float mfLeftTrigger = 0.0f;
	float mfRightTrigger = 0.0f;

	bool mbConnected = false;
};