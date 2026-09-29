#include"Scene.h"
#include "ObjectManager.h"
#include "UIManager.h"
#include "CollisionManager.h"

Scene::Scene()
{
	mpObjectManager = new ObjectManager();
	mpUIManager = new UIManager();
	mpCollisionManager = new CollisionManager();
}

Scene::~Scene()
{
	// -- 所有するポインタの解放 -- //
	delete mpObjectManager;
	mpObjectManager = nullptr;

	delete mpUIManager;
	mpUIManager = nullptr;

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

	if (mpUIManager != nullptr)
	{
		mpUIManager->Clear();
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

	if (mpObjectManager != nullptr)
	{
		mpObjectManager->ResolveCollision();
	}
}

void Scene::Draw()
{
	if (mpObjectManager != nullptr)
	{
		mpObjectManager->Draw();
	}

	if (mpUIManager != nullptr)
	{
		mpUIManager->Draw();
	}
}






