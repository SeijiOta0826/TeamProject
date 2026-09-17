#pragma once
#include "Module.h"

class Graphic : public Module
{
public:
	Graphic() = default;
	~Graphic() = default;

	void Update() override;
	void Draw() override;
};