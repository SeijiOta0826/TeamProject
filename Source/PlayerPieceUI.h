#pragma once
#include "UI.h"

class PlayerPieceUI : public UI
{
public:
	PlayerPieceUI() = default;
	~PlayerPieceUI() = default;

	void Init() override;

	void Update() override;
	void Draw() override;

	// -- 選択状態のアクセサ -- //
	bool IsSelected() { return mbSelected; }
	void SetSelected(bool _selected) { mbSelected = _selected; }
	void ToggleSelected() { mbSelected = !mbSelected; }

private:
	bool mbSelected = true;
};