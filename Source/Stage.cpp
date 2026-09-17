#include "Stage.h"

#include "CsvLoader.h"

// Obj生成用
#include "Master.h"
#include "SceneManager.h"
#include "Scene.h"
#include "ObjectManager.h"

// 生成するObj関係
#include "Player.h"
#include "StageBlock.h"

#include "Transform.h"

#include "GameConfig.h"

#include <DxLib.h>  // VECTOR用

void Stage::Load(const std::string& _filename)
{
	mStageData = CsvLoader::Load(_filename);

	CreateObjects();
}

void Stage::CreateObjects()
{
    auto* objectManager =
        Master::mpSceneManager
        ->GetCurrentScene()
        ->GetObjectManager();

    for (int y = 0; y < mStageData.size(); y++)
    {
        for (int x = 0; x < mStageData[y].size(); x++)
        {
            const int tile = mStageData[y][x];

            switch (tile)
            {
            case 0:
                // 何も生成しない
                break;

            case 1:
            {
                // 床を生成
                auto stageBlock = objectManager
                    ->CreateObject<StageBlock>();

                stageBlock->GetModule<Transform>()
                    ->SetPosition(
                        VGet(
                            (x * GameConfig::CELL_SIZE) + GameConfig::CELL_SIZE,
                            (y * GameConfig::CELL_SIZE) + GameConfig::CELL_SIZE,
                            0.0f
                        )
                    );
                break;
            }
            default:
                break;
            }
        }
    }
}