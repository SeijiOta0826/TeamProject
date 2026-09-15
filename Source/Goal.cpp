#include "Goal.h"

#include "Collider.h"

Goal::Goal(std::string filename, VECTOR initPos)
	:GameObject(filename, initPos)
{
	SetTag(Tag::GOAL);

	mpCollider->SetHalfSize(
		VGet(50.0f, 50.0f, 0.0f)
	);
}

Goal::~Goal()
{
}

void Goal::Update(float _deltaTime)
{
}

void Goal::Draw()
{
	Object2D::Draw();
}