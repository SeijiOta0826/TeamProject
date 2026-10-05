#include "PlayerPieceButton.h"

#include "Debug.h"

void PlayerPieceButton::Init()
{
	auto& transform = GetTransform();
	transform.SetAnchor(VGet(0.5f, 0.5f, 0.0f));
	transform.SetPosition(VGet(100.0f, 100.0f, 0.0f));

	auto& text = GetText();
	text.SetText("うんこ");
}

void PlayerPieceButton::Update()
{
	if (GetButton().IsMouseInside())
		Debug::Print("挿入ってりゅ～");
}

void PlayerPieceButton::Draw()
{
	UI::Draw();
}