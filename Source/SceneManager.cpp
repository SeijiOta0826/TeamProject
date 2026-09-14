#include "SceneManager.h"
#include "Scene.h"
#include "Master.h"

#include "GameScene.h"
#include "StageSelectScene.h"

SceneManager::SceneManager()
	:mnSceneType(SCENE_TYPE::SCENE_NONE)
	, mnNextSceneType(SCENE_TYPE::SCENE_NONE)
	, mpCurrentScene(nullptr)
{

}

void SceneManager::Initialize()
{
	// -- 初期シーンの設定 -- //
	mnNextSceneType = SCENE_TYPE::STAGE_SELECT_SCENE;
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
	case SCENE_TYPE::STAGE_SELECT_SCENE:
		mpCurrentScene = new StageSelectScene();
		break;

	case SCENE_TYPE::GAME_SCENE:
	{
		auto* gameScene = new GameScene();

		gameScene->SetStageNumber(mnStageNumber);

		mpCurrentScene = gameScene;
		break;
	}

	default:
		break;
	}

	mpCurrentScene->Initialize();	// 新シーンの初期処理をする
}

void SceneManager::SetStageNumber(int _stageNumber)
{
	mnStageNumber = _stageNumber;
}

int SceneManager::GetStageNumber() const
{
	return mnStageNumber;
}

void SceneManager::Finalize()
{
	// -- 解放 -- //
	delete mpCurrentScene;
	mpCurrentScene = nullptr;
}

