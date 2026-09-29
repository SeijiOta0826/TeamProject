#include "UIManager.h"

#include "UI.h"

void UIManager::Draw()
{
    for (auto& ui : mUIs) 
    {
        ui->Draw();
    }
}

void UIManager::Clear() {
    mUIs.clear();
}