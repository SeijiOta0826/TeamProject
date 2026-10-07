#include "Stage.h"

#include "CsvLoader.h"

// Obj生成用
#include "Master.h"
#include "SceneManager.h"
#include "Scene.h"
#include "ObjectManager.h"
#include "Player.h"

// 生成するObj関係
#include "Player.h"
#include "StageBlock.h"
#include "Goal.h"
#include "MovingBlock.h"
#include "Spike.h"
#include "DisappearingBlock.h"
#include "Switch.h"
#include "SwitchBlock.h"

#include "Transform.h"

#include "GameConfig.h"

#include <DxLib.h>  // VECTOR用

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

    // オブジェクトを生成
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
                        300.0f,
                        800.0f,
                        2.0f
                    );

                break;
            }

            case 4:
            {
                // 針を生成
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

            case 6:
            {
                // 消える床を生成
                objectManager
                    ->CreateObject<DisappearingBlock>();

                break;
            }

            case 7:
            {
                // スイッチを生成
                objectManager
                    ->CreateObject<Switch>(
                        "Resource/Help.png",
                        VGet(
                            (x * GameConfig::CELL_SIZE) + GameConfig::CELL_SIZE / 2.0f,
                            (y * GameConfig::CELL_SIZE) + GameConfig::CELL_SIZE / 2.0f,
                            0.0f
                        )
                    );

                break;
            }

            case 8:
                // SwitchBlockは2回目に生成する
                break;

            }
            default:
                break;
            }
        }
    }

    // Switchを取得
    Switch* pSwitch = objectManager->FindObject<Switch>();

    if (pSwitch == nullptr)
        return;

    // SwitchBlockを生成
    for (int y = 0; y < mStageData.size(); y++)
    {
        for (int x = 0; x < mStageData[y].size(); x++)
        {
            const int tile = mStageData[y][x];

            if (tile != 8)
                continue;

            objectManager
                ->CreateObject<SwitchBlock>(
                    "Resource/Stage/Stage.png",
                    VGet(
                        (x * GameConfig::CELL_SIZE) + GameConfig::CELL_SIZE / 2.0f,
                        (y * GameConfig::CELL_SIZE) + GameConfig::CELL_SIZE / 2.0f,
                        0.0f
                    ),
                    pSwitch
                );
        }
    }
}

void Stage::SetPlayerRespawn(Player* _player)
{
    if (_player == nullptr)
        return;

    _player->SetRespawnPos(mvRespawnPos);
}