#include "UIManager.h"

#include "UI.h"

void UIManager::Update()
{
    for (auto& ui : mUIs)
    {
        ui->Update();
    }
}

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