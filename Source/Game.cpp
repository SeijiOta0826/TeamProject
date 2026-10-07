#include "Game.h"
#include "ScreenConfig.h"
#include "InputManager.h"
#include "Master.h"

#include <algorithm>
#include <chrono>

using namespace std::chrono_literals;

// -------------------------------------------------------------
// 静的メンバ変数の実体定義（Masterクラス連携用）
// -------------------------------------------------------------
SceneManager* Master::mpSceneManager{ nullptr };
ResourceManager* Master::mpResource{ nullptr };
FontManager* Master::mpFontManager{ nullptr };

Game::Game()
{
    // 1. DxLib初期化
    if (!InitializeDxLib()) {
        return;
    }

    // 2. Masterへのアドレス登録（依存順）
    Master::mpResource = &m_resourceManager;
    Master::mpFontManager = &m_fontManager;
    Master::mpSceneManager = &m_sceneManager;

    // 3. 各マネージャー・オブジェクトの初期化
    InputManager::GetInstance().InitializeButton();
    InputManager::GetInstance().InitializeAxis();
    m_cursor.Initialize();

    m_sceneManager.Initialize();

    m_initSuccess = true;
    m_isRunning = true;
    m_lastFrameTime = std::chrono::steady_clock::now();
}

Game::~Game()
{
    if (m_initSuccess) {
        // 生成と逆順で破棄処理
        m_cursor.Finalize();
        m_sceneManager.Finalize();
        m_fontManager.Clear();

        // 破棄前にポインタを null に戻す（ダングリングポインタ対策）
        Master::mpSceneManager = nullptr;
        Master::mpFontManager = nullptr;
        Master::mpResource = nullptr;
    }

    DxLib_End();
}

bool Game::InitializeDxLib()
{
    ChangeWindowMode(TRUE);
    SetGraphMode(
        static_cast<int>(ScreenConfig::SCREEN_WIDTH),
        static_cast<int>(ScreenConfig::SCREEN_HEIGHT),
        32
    );
    SetMainWindowText("Game");

    // 垂直同期（V-Sync）を有効化
    SetWaitVSyncFlag(TRUE);

    if (DxLib_Init() == -1) {
        return false;
    }

    // 描画バッファ・ライティング設定
    SetDrawScreen(DX_SCREEN_BACK);
    SetUseZBufferFlag(TRUE);
    SetWriteZBufferFlag(TRUE);
    SetUseLighting(TRUE);
    SetLightDifColor(GetColorF(1.0f, 0.8f, 0.4f, 0.0f));
    SetLightAmbColor(GetColorF(3.2f, 3.2f, 3.2f, 0.0f));

    return true;
}

void Game::Run()
{
    if (!m_initSuccess) {
        return;
    }

    while (m_isRunning && ProcessMessage() == 0) {
        if (CheckHitKey(KEY_INPUT_ESCAPE) != 0) {
            m_isRunning = false;
            break;
        }

        // 入力ポーリング（1フレームに1回のみ）
        InputManager::GetInstance().Update();

        // デルタタイム算出
        const auto currentTime = std::chrono::steady_clock::now();
        std::chrono::duration<double> frameTime = currentTime - m_lastFrameTime;
        m_lastFrameTime = currentTime;

        // C++20 std::clamp によるスパイク対策（最大0.2秒に制限）
        frameTime = std::clamp(frameTime, 0.0s, 0.2s);
        m_accumulator += frameTime;

        // 固定タイムステップ更新（スパイラル・オブ・デス防止ガード付き）
        int stepCount{ 0 };
        const std::chrono::duration<double> fixedStep = FIXED_TIMESTEP;

        while (m_accumulator >= fixedStep && stepCount < MAX_SIMULATION_STEPS) {
            UpdateLogic(fixedStep.count());
            m_accumulator -= fixedStep;
            ++stepCount;
        }

        Draw();
        ScreenFlip();
    }
}

void Game::UpdateLogic(double deltaTime)
{
    m_cursor.Update();
    m_sceneManager.Update(static_cast<float>(deltaTime));
}

void Game::Draw()
{
    ClearDrawScreen();
    m_sceneManager.Draw();
    m_cursor.Draw();
}