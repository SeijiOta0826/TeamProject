#include "ObjectManager.h"

#include "Object2D.h"

void ObjectManager::Update(float _deltaTime) {
    for (auto& object : mObjects) {
        object->Update(_deltaTime);
    }

    RemoveDestroyObjects();
}

void ObjectManager::Draw() {
    for (auto& object : mObjects) {
        if (object->GetTag() != Tag::PLAYER)
        {
            object->Draw();
        }
    }

    for (auto& object : mObjects) {
        if (object->GetTag() == Tag::PLAYER)
        {
            object->Draw();
        }
    }
}

void ObjectManager::RemoveDestroyObjects() {
    std::erase_if(
        mObjects,
        [](const auto& object) {
        return object->IsDestroy();
    }
    );
}

void ObjectManager::Clear() {
    mObjects.clear();
}