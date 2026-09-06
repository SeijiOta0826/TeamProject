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
	delete mpObjectManager;
	mpObjectManager = nullptr;

	delete mpCollisionManager;
	mpCollisionManager = nullptr;
}

void Scene::Finalize() {
	mpCollisionManager->Finalize();
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






