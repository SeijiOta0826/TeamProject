#pragma once
#include <string>
#include <vector>
#include <sstream>
#include "DxLib.h"
#include "FloatingMotion.h"

enum class TextAlign
{
    Left,
    Center,
    Right
};

class UILabel
{
public:
    UILabel() = default;

    // 通常の静止テキスト用コンストラクタ
    UILabel(int x, int y, const std::string& text, unsigned int color, int fontHandle = -1, TextAlign align = TextAlign::Left)
        : mX(x), mY(y), mText(text), mColor(color), mFontHandle(fontHandle), mAlign(align), mUseMotion(false)
    {
    }

    // ふわふわ演出つきコンストラクタ
    UILabel(int x, int y, const std::string& text, unsigned int color, int fontHandle, const FloatingMotion& motion, TextAlign align = TextAlign::Left)
        : mX(x), mY(y), mText(text), mColor(color), mFontHandle(fontHandle), mAlign(align), mMotion(motion), mUseMotion(true)
    {
    }

    // 演出を後から付与・変更する場合
    void SetMotion(const FloatingMotion& motion)
    {
        mMotion = motion;
        mUseMotion = true;
    }

    // 毎フレーム呼ぶ更新処理（モーションが有効なときだけ進む）
    void Update()
    {
        if (mUseMotion)
        {
            mMotion.Update();
        }
    }

    // 描画処理
    void Draw() const
    {
        float offsetY = mUseMotion ? mMotion.GetOffsetY() : 0.0f;
        int drawBaseY = mY + static_cast<int>(offsetY);

        // 改行コード（\n）ごとに分割して描画
        std::vector<std::string> lines = SplitLines(mText);
        int fontHeight = (mFontHandle != -1) ? GetFontSizeToHandle(mFontHandle) : 16;
        int lineSpacing = 4; // 行間ピクセル数

        int currentY = drawBaseY;
        for (const auto& line : lines)
        {
            int drawX = mX;
            int width = (mFontHandle != -1)
                ? GetDrawStringWidthToHandle(line.c_str(), static_cast<int>(line.length()), mFontHandle)
                : GetDrawStringWidth(line.c_str(), static_cast<int>(line.length()));

            if (mAlign == TextAlign::Center)
            {
                drawX -= width / 2;
            }
            else if (mAlign == TextAlign::Right)
            {
                drawX -= width;
            }

            if (mFontHandle != -1)
            {
                DrawStringToHandle(drawX, currentY, line.c_str(), mColor, mFontHandle);
            }
            else
            {
                DrawString(drawX, currentY, line.c_str(), mColor);
            }

            currentY += fontHeight + lineSpacing;
        }
    }

    // 設定変更用セッター
    void SetText(const std::string& text) { mText = text; }
    void SetPosition(int x, int y) { mX = x; mY = y; }
    void SetColor(unsigned int color) { mColor = color; }

    // 単発でサッと描画したいときの静的関数（PAUSEやボタンの文字など）
    static void DrawImmediate(int x, int y, const std::string& text, unsigned int color, int fontHandle = -1, TextAlign align = TextAlign::Left)
    {
        UILabel tempLabel(x, y, text, color, fontHandle, align);
        tempLabel.Draw();
    }

private:
    static std::vector<std::string> SplitLines(const std::string& text)
    {
        std::vector<std::string> lines;
        std::stringstream ss(text);
        std::string line;
        while (std::getline(ss, line))
        {
            lines.push_back(line);
        }
        return lines;
    }

    int mX = 0;
    int mY = 0;
    std::string mText;
    unsigned int mColor = 0xFFFFFF;
    int mFontHandle = -1;
    TextAlign mAlign = TextAlign::Left;

    FloatingMotion mMotion;
    bool mUseMotion = false;
};