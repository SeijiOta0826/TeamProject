#include "SceneManager.h"
#include "Scene.h"
#include "Master.h"

#include "GameScene.h"

SceneManager::SceneManager()
	:mnSceneType(SCENE_TYPE::SCENE_NONE)
	, mnNextSceneType(SCENE_TYPE::SCENE_NONE)
	, mpCurrentScene(nullptr)
{

}

void SceneManager::Initialize()
{
	// -- 初期シーンの設定 -- //
	mnNextSceneType = SCENE_TYPE::GAME_SCENE;
	ChangeSceneIfNeeded();
}

void SceneManager::Update(float _deltaTime)
{
	mpCurrentScene->Update(_deltaTime);
}

void SceneManager::Draw()
{
	mpCurrentScene->Draw();
}

void SceneManager::Finalize()
{
	// -- 解放 -- //
	delete mpCurrentScene;
	mpCurrentScene = nullptr;
}

void SceneManager::ChangeSceneIfNeeded()
{
	if (mnSceneType == mnNextSceneType)
		return;
	
	if (mpCurrentScene != nullptr)
	{
		mpCurrentScene->Finalize();	// 旧シーンの終了処理をする
	}

	mnSceneType = mnNextSceneType;	// 次シーンにするためシーンタイプを更新

	switch (mnSceneType)
	{
	case SCENE_TYPE::GAME_SCENE:
		mpCurrentScene = new GameScene();
		break;
	default:
		break;
	}

	mpCurrentScene->Initialize();	// 新シーンの初期処理をする
}