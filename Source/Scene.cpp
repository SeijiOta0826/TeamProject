#include"Scene.h"
#include "ObjectManager.h"

Scene::Scene()
{
	mpObjectManager = new ObjectManager();
}

Scene::~Scene()
{
	delete mpObjectManager;
	mpObjectManager = nullptr;
}

void Scene::Update(float _deltaTime)
{
	if (mpObjectManager != nullptr)
	{
		mpObjectManager->Update(_deltaTime);
	}
}

void Scene::Draw()
{
	if (mpObjectManager != nullptr)
	{
		mpObjectManager->Draw();
	}
}






