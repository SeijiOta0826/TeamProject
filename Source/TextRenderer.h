#pragma once

#include <string>
#include <vector>
#include <sstream>
#include "DxLib.h"

enum class TextAlign
{
    Left,
    Center,
    Right
};

class TextRenderer
{
public:
    // 通常の直接描画（静的関数としてどこからでも呼び出し可能）
    static void Draw(
        int x,
        int y,
        const std::string& text,
        unsigned int color,
        int fontHandle = -1,
        TextAlign align = TextAlign::Left)
    {
        std::vector<std::string> lines = SplitLines(text);
        int currentY = y;
        int fontHeight = (fontHandle != -1) ? GetFontSizeToHandle(fontHandle) : 16;
        int lineSpacing = 4; // 行間

        for (const auto& line : lines)
        {
            int drawX = x;
            int width = (fontHandle != -1)
                ? GetDrawStringWidthToHandle(line.c_str(), static_cast<int>(line.length()), fontHandle)
                : GetDrawStringWidth(line.c_str(), static_cast<int>(line.length()));

            if (align == TextAlign::Center)
            {
                drawX -= width / 2;
            }
            else if (align == TextAlign::Right)
            {
                drawX -= width;
            }

            if (fontHandle != -1)
            {
                DrawStringToHandle(drawX, currentY, line.c_str(), color, fontHandle);
            }
            else
            {
                DrawString(drawX, currentY, line.c_str(), color);
            }

            currentY += fontHeight + lineSpacing;
        }
    }

private:
    // 改行コード (\n) で分割する補助関数
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
};