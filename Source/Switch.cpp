#include "Switch.h"

#include "Player.h"
#include "Collider.h"
#include "Gravity.h"

void Switch::Init()
{
    SetTag(Tag::BLOCK);
    GetModule<Collider>()->AddCollisionTag(Tag::PLAYER);

    GetModule<Gravity>()->SetEnabled(false);    // 重力を無効化
}

void Switch::Update(float _deltaTime)
{
    if (_deltaTime <= 0.0f)
        return;

    CheckPlayer();

    GameObject::Update(_deltaTime);
}

void Switch::CheckPlayer()
{
    // すでにONなら何もしない
    if (mbIsActivated)
        return;

    auto collisions = GetModule<Collider>()->GetCollisions(Tag::PLAYER);

    for (auto* playerObject : collisions)
    {
        if (playerObject == nullptr)
            continue;

        Player* player = dynamic_cast<Player*>(playerObject);

        if (player == nullptr)
            continue;

        // プレイヤーが踏んだ
        mbIsActivated = true;

        // スイッチをON状態の見た目に変更
        // mpTexture->SetTexture("Resource/Player.png");

        break;
    }
}