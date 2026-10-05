#include "Switch.h"

#include "Player.h"
#include "Collider.h"
#include "Gravity.h"
#include "Texture.h"

Switch::Switch(
    std::string filename,
    VECTOR initPos
)
    : GameObject(filename, initPos)
{
    SetTag(Tag::BLOCK);

    mpCollider->AddCollisionTag(Tag::PLAYER);

    // スイッチは落下しない
    mpGravity->SetEnable(false);
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

    auto collisions = mpCollider->GetCollisions(Tag::PLAYER);

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
        mpTexture->SetTexture("Resource/Player.png");

        break;
    }
}