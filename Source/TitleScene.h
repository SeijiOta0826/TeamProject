#pragma once

#include "Scene.h"

class TitleScene : public Scene
{
public:
	void Initialize() override;
	void Update(float _deltaTime) override;
	void Draw() override;
	void Finalize() override;
private:
	bool mbStartSelected = false;
	bool mbPreviousMouseLeft = false;
};