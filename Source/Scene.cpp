#include"Scene.h"
#include "ObjectManager.h"
#include "CollisionManager.h"

Scene::Scene()
{
	mpObjectManager = new ObjectManager();
	mpCollisionManager = new CollisionManager();
}

Scene::~Scene()
{
	// -- 所有するポインタの解放 -- //
	delete mpObjectManager;
	mpObjectManager = nullptr;

	delete mpCollisionManager;
	mpCollisionManager = nullptr;
}

void Scene::Finalize() {
	// -- CollisionManagerに登録されているCollider群の解放 -- //
	if (mpCollisionManager != nullptr)
	{
		mpCollisionManager->Finalize();
	}

	// -- ObjectManagerの所有するObject群の解放 -- //
	if (mpObjectManager != nullptr)
	{
		mpObjectManager->Clear();
	}
}

void Scene::Update(float _deltaTime)
{
	if (mpObjectManager != nullptr)
	{
		mpObjectManager->Update(_deltaTime);
	}

	if (mpCollisionManager != nullptr)
	{
		mpCollisionManager->Update();
	}
}

void Scene::Draw()
{
	if (mpObjectManager != nullptr)
	{
		mpObjectManager->Draw();
	}
}






