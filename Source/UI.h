#pragma once

// Todo : コンポジットする部品のインクルードをここへ
#include  "UITransform.h"
#include "UIGraphic.h"

class UIManager;

class UI
{
public:
	UI() = default;
	virtual ~UI() = default;

	void Update();
	void Draw();

	UITransform GetTransform() { return mTransform; }
	UIGraphic GetGraphic() { return mGraphic; }

	UIManager* GetUIManager() { return mpUIManager; }

private:
	friend class UIManager;
	UIManager* mpUIManager;
	void Initialize(UIManager* _manager);

private:
	// コンポジットする部品の実体の宣言をここへ
	UITransform mTransform;
	UIGraphic mGraphic;
};