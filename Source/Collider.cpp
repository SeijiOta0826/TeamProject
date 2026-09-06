#include "Collider.h"

#include "CollisionManager.h"
#include "Master.h"
#include "SceneManager.h"
#include "Scene.h"

#include "Object2D.h"

Collider::Collider(Object2D* _obj) 
{
	mpObj = _obj;
}

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
	for (auto* collider : mCollisions) {
		if (collider->GetObject2D()->GetTag() == _tag) {
			return true;
		}
	}

	return false;
}

Object2D* Collider::GetCollision(Tag _tag) const
{
	for (auto* collider : mCollisions) {
		Tag tag = collider->GetObject2D()->GetTag();
		if (tag == _tag) {
			return collider->GetObject2D();
		}
	}

	return nullptr;
}

VECTOR Collider::GetWorldPosition() const {
	return
		VAdd(
			mpObj->GetPosition(),
			mvOffSetPos
		);
}