#include "UIText.h"

#include "UI.h"

void UIText::Initialize(UI* _pUI)
{
	mpUI = _pUI;
}

void UIText::Draw()
{
	auto transform =
		mpUI->GetTransform();
	VECTOR basePosition = VSub(
		transform.GetPosition(),
		VGet(transform.GetSize().x / 2.0f,
			transform.GetSize().y / 2.0f,
			0.0f
		)
	);

	int textWidth = GetDrawStringWidth(
		mText.c_str(),
		static_cast<int>(mText.size()),
		mnFontSize
	);

	int drawX = static_cast<int>(basePosition.x);

	switch (mAlign)
	{
	case TextAlign::LEFT:
		break;

	case TextAlign::CENTER:
		drawX -= textWidth / 2;
		break;

	case TextAlign::RIGHT:
		drawX -= textWidth;
		break;
	}
}