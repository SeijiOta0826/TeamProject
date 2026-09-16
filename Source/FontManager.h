#pragma once
#include "DxLib.h"
#include <string>
#include <unordered_map>

class FontManager {
public:
    // ★ コンストラクタとデストラクタを public に配置する
    FontManager() = default;
    ~FontManager() { Clear(); }

    // コピー禁止（意図しないコピー防止）
    FontManager(const FontManager&) = delete;
    FontManager& operator=(const FontManager&) = delete;

	//-- フォントの取得と解放--//  ->thickのデフォルト値を-1に設定することで、太さを指定しない場合はデフォルトの太さが使用されるようにする
    int GetFont(const std::string& fontName, int size, int thick = -1, int fontType = DX_FONTTYPE_ANTIALIASING);
    void ReleaseFont(const std::string& fontName, int size, int thick = -1, int fontType = DX_FONTTYPE_ANTIALIASING);
    void Clear();

private:
    std::string GenerateKey(const std::string& fontName, int size, int thick, int fontType) const {
        return fontName + "_" + std::to_string(size) + "_" + std::to_string(thick) + "_" + std::to_string(fontType);
    }

    std::unordered_map<std::string, int> fontMap_;
};