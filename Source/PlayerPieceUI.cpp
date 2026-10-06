#include "PlayerPieceUI.h"

#include "Debug.h"

void PlayerPieceUI::Init()
{
	LoadUIGraph("Resource/Obj/test_field.png");

	auto& transform = GetTransform();
	transform.SetAnchor(VGet(0.5f, 0.5f, 0.0f));
	transform.SetPosition(VGet(100.0f, 100.0f, 0.0f));

	auto& text = GetText();
	text.SetText("うんこ");
}

void PlayerPieceUI::Update()
{
	if (GetButton().IsMouseInside())
		Debug::Print("挿入ってりゅ～");
}

void PlayerPieceUI::Draw()
{
	UI::Draw();
}