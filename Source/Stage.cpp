#include "Stage.h"

#include "CsvLoader.h"

#include "Master.h"
#include "SceneManager.h"
#include "Scene.h"
#include "ObjectManager.h"
#include "Player.h"

#include "StageBlock.h"
#include "Goal.h"
#include "MovingBlock.h"
#include "Spike.h"

#include "GameConfig.h"


void Stage::Load(const std::string& _filename)
{
	mStageData = CsvLoader::Load(_filename);
    
    if (mStageData.empty())
    {
        OutputDebugStringA("Stage CSVが読み込めていません\n");
    }
    else
    {
        OutputDebugStringA("Stage CSV読み込み成功\n");
    }

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
                        "Resource/Stage/Stage.png",
                        VGet(
                            (x * GameConfig::CELL_SIZE) + GameConfig::CELL_SIZE / 2.0f,
                            (y * GameConfig::CELL_SIZE) + GameConfig::CELL_SIZE / 2.0f,
                            0.0f
                        )
                    );
                break;
            
            case 2:
            {
                // ゴールの形
                bool goalShape[3][3] =
                {
                    { false, false, false },
                    { false, true,  false },
                    { false, false, false }
                };

                // ゴールを生成
                objectManager
                    ->CreateObject<Goal>(
                        "Resource/Help.png",
                        VGet(
                            (x * GameConfig::CELL_SIZE) + GameConfig::CELL_SIZE / 2.0f,
                            (y * GameConfig::CELL_SIZE) + GameConfig::CELL_SIZE / 2.0f,
                            0.0f
                        ),
                        goalShape
                    );

                break;
            }

            case 3:
            {
                // 動く床を生成
                objectManager
                    ->CreateObject<MovingBlock>(
                        "Resource/Stage/Stage.png",
                        VGet(
                            (x * GameConfig::CELL_SIZE) + GameConfig::CELL_SIZE / 2.0f,
                            (y * GameConfig::CELL_SIZE) + GameConfig::CELL_SIZE / 2.0f,
                            0.0f
                        ),
                        300.0f,
                        800.0f,
                        2.0f
                    );

                break;
            }

            case 4:
            {
                objectManager
                    ->CreateObject<Spike>(
                        "Resource/Spike.png",
                        VGet(
                            (x * GameConfig::CELL_SIZE) + GameConfig::CELL_SIZE / 2.0f,
                            (y * GameConfig::CELL_SIZE) + GameConfig::CELL_SIZE / 2.0f,
                            0.0f
                        )
                    );
                break;
            }

            case 5:
            {
                // リスポーン地点を設定
                mvRespawnPos = VGet(
                    (x * GameConfig::CELL_SIZE) + GameConfig::CELL_SIZE / 2.0f,
                    (y * GameConfig::CELL_SIZE) + GameConfig::CELL_SIZE / 2.0f,
                    0.0f
                );

                break;
            }

            default:
                break;
            }
        }
    }
}

void Stage::SetPlayerRespawn(Player* _player)
{
    if (_player == nullptr)
        return;

    _player->SetRespawnPos(mvRespawnPos);
}