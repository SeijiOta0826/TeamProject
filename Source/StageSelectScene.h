#pragma once

#include "Scene.h"

class StageSelectScene : public Scene
{
public:
	void Initialize() override;
	void Update(float _deltaTime) override;
	void Draw() override;
	void Finalize() override;

private:
	int mnSelectedStage = 0;
};