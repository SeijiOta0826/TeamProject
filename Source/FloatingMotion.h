#pragma once
#include <cmath>

class FloatingMotion {
public:
    // fontMoveFrames: 1往復にかかるフレーム数（60なら約1秒で1往復）
    // pixel: 上下に動く幅（8.0fなら上下8px）
    FloatingMotion(int fontMoveFrames = 60, float pixel = 8.0f)
        : fontMoveFrames_(fontMoveFrames), pixel_(pixel), currentFrames_(0) {
    }

    // 毎フレーム呼んでカウントを進める
    void Update() {
        currentFrames_++;
        if (currentFrames_ >= fontMoveFrames_) {
            currentFrames_ = 0; // 0に戻して繰り返す
        }
    }

    // 現在のY軸のズレ（何ピクセル動かすか）を取得
    float GetOffsetY() const {
        // 進行度（0.0 ? 1.0）
        float progress = static_cast<float>(currentFrames_) / static_cast<float>(fontMoveFrames_);
        // 1周のSin波（6.2831853f ≒ 2π）で滑らかに揺らす
        return std::sin(progress * 6.2831853f) * pixel_;
    }

private:
    int fontMoveFrames_; // 周期（フレーム数）
    float pixel_;          // 揺れ幅（ピクセル）
    int currentFrames_;    // 現在のフレーム
};