#include "UIManager.h"

#include "UI.h"

#include <algorithm>

void UIManager::Update()
{
    for (auto& ui : mUIs)
    {
        ui->Update();
    }
}

void UIManager::Draw()
{
    std::sort(
        mUIs.begin(),
        mUIs.end(),
        [](UI* _a, UI* _b)
        {
            return _a->GetLayer() < _b->GetLayer();
        }
    );

    for (auto& ui : mUIs) 
    {
        ui->Draw();
    }
}

void UIManager::Clear() {
    mUIs.clear();
}