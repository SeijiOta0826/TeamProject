#pragma once
#include "Module.h"

#include <DxLib.h>	// VECTOR用
#include <string>	// ファイル名用

class Graphic : public Module
{
public:
	Graphic(std::string _filename);
	~Graphic() = default;

	void Initialize() override;

	void Draw() override;

private:
	int mnGraphHandle = -1;
	VECTOR mvSize = VGet(0.0f, 0.0f, 0.0f);
};