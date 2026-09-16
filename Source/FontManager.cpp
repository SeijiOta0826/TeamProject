#include "FontManager.h"

int FontManager::GetFont(const std::string& fontName, int size, int thick, int fontType) {
    std::string key = GenerateKey(fontName, size, thick, fontType);

    // すでにキャッシュにある場合は既存のハンドルを返す
    auto it = fontMap_.find(key);
    if (it != fontMap_.end()) {
        return it->second;
    }

    // キャッシュにない場合は新規作成
    int handle = CreateFontToHandle(
        fontName.empty() ? nullptr : fontName.c_str(),
        size,
        thick,
        fontType
    );

    if (handle != -1) {
        fontMap_[key] = handle;
    }

    return handle;
}

void FontManager::ReleaseFont(const std::string& fontName, int size, int thick, int fontType) {
    std::string key = GenerateKey(fontName, size, thick, fontType);
    auto it = fontMap_.find(key);
    if (it != fontMap_.end()) {
        DeleteFontToHandle(it->second);
        fontMap_.erase(it);
    }
}

void FontManager::Clear() {
    for (auto& pair : fontMap_) {
        DeleteFontToHandle(pair.second);
    }
    fontMap_.clear();
}