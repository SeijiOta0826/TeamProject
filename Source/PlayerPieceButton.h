#pragma once
#include "UI.h"

class PlayerPieceButton : public UI
{
public:
	PlayerPieceButton() = default;
	~PlayerPieceButton() = default;

	void Init() override;

	void Update() override;
	void Draw() override;

protected:
	const char* GetGraphFilename() const override
	{ 
		return "Resource/Obj/test_field.png"; 
	}
};