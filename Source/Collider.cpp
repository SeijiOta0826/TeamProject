#include "Collider.h"

#include "CollisionManager.h"
#include "Master.h"
#include "SceneManager.h"
#include "Scene.h"

#include "GameObject.h"
#include "Transform.h"

void Collider::Initialize() {
	Master::mpSceneManager
		->GetCurrentScene()
		->GetCollisionManager()
		->Register(this);
}

void Collider::Finalize() {
	Master::mpSceneManager
		->GetCurrentScene()
		->GetCollisionManager()
		->Unregister(this);
}

bool Collider::IsColliding() const {
	return !mCollisions.empty();
}

bool Collider::IsColliding(Tag _tag) const
{
	for (auto collider : mCollisions) 
	{
		if (collider->GetGameObject()->GetTag() == _tag)
		{
			return true;
		}
	}

	return false;
}

std::vector<GameObject*> Collider::GetCollisions(Tag _tag)
{
	std::vector<GameObject*> objects;

	for (auto collider : mCollisions)
	{
		auto* gameObject = collider->GetGameObject();
		Tag tag = gameObject->GetTag();
		if (tag == _tag)
		{
			objects.push_back(gameObject);
		}
	}

	return objects;
}

VECTOR Collider::GetWorldPosition() const
{
	auto transform = mpGameObject->GetModule<Transform>();
	if (transform == nullptr)
		return;

	return
		VAdd(
			transform->GetPosition(),
			mvOffSetPos
		);
}