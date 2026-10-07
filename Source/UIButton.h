#pragma once

#pragma once

class UI;

class UIButton
{
public:
    UIButton() = default;
    ~UIButton() = default;

    void Initialize(UI* _pUI);

    // マウスカーソルがUIの範囲内にあるか
    bool IsMouseInside();

    // このフレームで決定入力が行われたか
    bool IsClicked();

private:
    UI* mpUI = nullptr;
};