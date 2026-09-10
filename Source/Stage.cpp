#include "Stage.h"

#include "CsvLoader.h"

#include "Master.h"
#include "SceneManager.h"
#include "Scene.h"
#include "ObjectManager.h"

#include "StageBlock.h"

#include "GameConfig.h"

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
                // 床を生成
                objectManager
                    ->CreateObject<StageBlock>(
                        "Resource/Stage.png",
                        VGet(
                            (x * GameConfig::CELL_SIZE) + GameConfig::CELL_SIZE / 2.0f,
                            (y * GameConfig::CELL_SIZE) + GameConfig::CELL_SIZE / 2.0f,
                            0.0f
                        )
                    );
                break;

            default:
                break;
            }
        }
    }
}