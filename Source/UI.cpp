#include "UI.h"

void UI::Initialize(UIManager* _manager)
{
	// Todo : 初期処理何かあり次第追加
	mpUIManager = _manager;

	mGraphic.Initialize(this,GetGraphFilename());
	mText.Initialize(this);

	Init();
}

void UI::Draw()
{
	// Todo : 要素が増え次第追加検討(主にstring)
	mGraphic.Draw();
	mText.Draw();
}