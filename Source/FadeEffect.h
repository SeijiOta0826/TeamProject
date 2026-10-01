#pragma once
#include <algorithm>
#include "DxLib.h"

// 画面遷移や演出用のフェード処理を管理・描画するクラス
class FadeEffect {
public:
    // フェードの状態
    enum class State {
        Idle,     // 停止中
        FadeIn,   // 暗転状態から徐々に画面を表示 (黒幕アルファ: 255 -> 0)
        FadeOut   // 画面から徐々に暗転 (黒幕アルファ: 0 -> 255)
    };

    // コンストラクタ
    // default_duration_frames: デフォルトのフェード所要フレーム数
public:
    explicit FadeEffect(int default_duration_frames = 60) {
        duration_frames_ = (default_duration_frames > 0) ? default_duration_frames : 1;
        current_frames_ = 0;
        state_ = State::Idle;
    }

    // フェードインを開始（画面を明るくする）
    // frames: フェードにかけるフレーム数（0以下の場合は前回の値を維持）
    void StartFadeIn(int frames = -1) {
        StartFade(State::FadeIn, frames);
    }

    // フェードアウトを開始（画面を暗くする）
    // frames: フェードにかけるフレーム数（0以下の場合は前回の値を維持）
    void StartFadeOut(int frames = -1) {
        StartFade(State::FadeOut, frames);
    }

    // 毎フレームの更新処理
    void Update() {
        if (state_ == State::Idle) {
            return;
        }

        current_frames_++;

        // 目標フレームに達したらフェード完了
        if (current_frames_ >= duration_frames_) {
            current_frames_ = duration_frames_;
            state_ = State::Idle;
        }
    }

    // フェード用オーバーレイ（黒幕）の描画
    // screen_width: 描画先の画面幅
    // screen_height: 描画先の画面高さ
    // color: 塗りつぶす色（デフォルトは黒）
    void Draw(int screen_width = 1280, int screen_height = 720, unsigned int color = 0) const {
        const int alpha = GetAlpha();
        if (alpha <= 0) {
            return; // 完全に透明なら描画負荷をスキップ
        }

        SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
        DrawBox(0, 0, screen_width, screen_height, (color == 0) ? GetColor(0, 0, 0) : color, TRUE);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    }

    // 現在の黒幕の不透明度を取得 (0: 完全透明 ? 255: 完全不透明)
    int GetAlpha() const {
        const float progress = GetProgress();

        switch (state_) {
        case State::FadeIn:
            // フェードイン中は時間経過とともに黒幕を薄くする (255 -> 0)
            return static_cast<int>((1.0f - progress) * 255.0f);

        case State::FadeOut:
            // フェードアウト中は時間経過とともに黒幕を濃くする (0 -> 255)
            return static_cast<int>(progress * 255.0f);

        case State::Idle:
        default:
            return 0;
        }
    }

    // フェードの進行度を取得 (0.0f ? 1.0f)
    float GetProgress() const {
        return static_cast<float>(current_frames_) / static_cast<float>(duration_frames_);
    }

    // フェード処理が終了しているか判定
    bool IsFinished() const {
        return state_ == State::Idle;
    }

    // 現在のフェード状態を取得
    State GetState() const {
        return state_;
    }

private:
    // 内部フェード開始共通処理
    void StartFade(State next_state, int frames) {
        if (frames > 0) {
            duration_frames_ = frames;
        }
        state_ = next_state;
        current_frames_ = 0;
    }

    int duration_frames_;  // フェード完了までの所要フレーム数
    int current_frames_;   // 現在の経過フレーム数
    State state_;          // 現在のフェード状態
};