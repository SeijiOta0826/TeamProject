#pragma once

#include "Scene.h"
#include <vector>

class StageSelectScene : public Scene
{
public:
	void Initialize() override;
	void Update(float _deltaTime) override;
	void Draw() override;
	void Finalize() override;

private:
	// 現在選択しているステージ
	int mnSelectedStage = 0;

	// 前フレームのマウス左クリック状態
	bool mbPreviousMouseLeft = true;

	// 選択中ステージのCSVデータ
	std::vector<std::vector<int>> mStageData;

	// 選択中ステージのプレビューを読み込む
	void LoadStagePreview();

	void DrawStagePreview();
};