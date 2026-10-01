#pragma once

// Todo : コンポジットする部品のインクルードをここへ
#include  "UITransform.h"
#include "UIGraphic.h"
#include "UIText.h"
#include "UIButton.h"

class UIManager;

class UI
{
public:
	UI() = default;
	virtual ~UI() = default;

	virtual void Init() = 0;		// 固有の初期化処理

	virtual void Update() {};
	virtual void Draw();

	UITransform& GetTransform() { return mTransform; }
	UIGraphic& GetGraphic() { return mGraphic; }
	UIText& GetText() { return mText; }
	UIButton& GetButton() { return mButton; }

	UIManager* GetUIManager() { return mpUIManager; }

private:
	friend class UIManager;
	UIManager* mpUIManager;
	void Initialize(UIManager* _manager);	// Manager内でUI生成時に通る

protected:
	virtual const char* GetGraphFilename() const { return ""; }

private:
	// Todo : コンポジットする部品の実体の宣言をここへ
	UITransform mTransform;
	UIGraphic mGraphic;
	UIText mText;
	UIButton mButton;
};