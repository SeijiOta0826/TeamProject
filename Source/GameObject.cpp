#include "GameObject.h"

#include "Collider.h"
#include "Gravity.h"

#include "Master.h"
#include "SceneManager.h"
#include "Scene.h"
// #include "ObjectManager.h"
#include "CollisionManager.h"

#include "GameConfig.h"

#include "Transform.h"
#include "Collider.h"

#include <cmath>

void GameObject::Initialize(ObjectManager* _manager) {
	mpObjectManager = _manager;
	this->InitComponent();	// 継承先が持つコンポーネント初期設定
	this->Init();			// 継承先特有の初期化処理

	for (auto& component : mModules) {
		if (component->IsEnabled()) {
			component->Initialize();
		}
	}
}

void GameObject::Finalize() {
	for (auto component = mModules.rbegin();
		component != mModules.rend();
		++component) {
		(*component)->Finalize();
	}
}

void GameObject::Update(float _deltaTime) {
	for (auto& component : mModules) {
		if (component->IsEnabled()) {
			component->Update();
		}
	}

	// ResolveCollision();
}

void GameObject::Draw() {
	for (auto& component : mModules) {
		if (component->IsEnabled()) {
			component->Draw();
		}
	}
}

void GameObject::ResolveCollision()
{
	// nullCheack
	auto myTransform = GetModule<Transform>();
	auto myCollider = GetModule<Collider>();
	if (!myTransform
		|| !myCollider)
		return;

	mbGrounded = false;
	mvCollisionCorrection = VGet(0.0f, 0.0f, 0.0f);

	auto* collisionManager =
		Master::mpSceneManager
		->GetCurrentScene()
		->GetCollisionManager();

	if (collisionManager == nullptr
		|| !myCollider->IsEnabled())
		return;

	auto tags = myCollider->GetCollisionTag();

	for (auto tag : tags)
	{
		auto objects = myCollider->GetCollisions(tag);
		for (auto obj : objects)
		{
			//auto collider = collision->GetCollider();
			auto collider = obj->GetModule<Collider>();
			if (collider == nullptr)
				continue;

			CollisionInfo info;

			if (!collisionManager->GetBoxBoxCollision(
				myCollider,
				collider,
				info))
			{
				continue;
			}

			if (info.normal.y < -0.5f)
				mbGrounded = true;

			VECTOR correction = VScale(
				info.normal,
				info.penetration
			);

			if (fabsf(correction.x) > fabsf(mvCollisionCorrection.x))
			{
				mvCollisionCorrection.x = correction.x;
			}

			if (fabsf(correction.y) > fabsf(mvCollisionCorrection.y))
			{
				mvCollisionCorrection.y = correction.y;
			}
		}
	}
}