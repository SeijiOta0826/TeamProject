#include "Spike.h"
#include "Player.h"
#include "Collider.h"
#include "Gravity.h"

Spike::Spike(std::string filename, VECTOR initPos)
    : GameObject(filename, initPos)
{
    // トゲのタグを設定
    SetTag(Tag::SPIKE);

    // Playerとの衝突を取得
    mpCollider->AddCollisionTag(Tag::PLAYER);

    // トゲは落下しない
    mpGravity->SetEnable(false);
}

void Spike::Update(float _deltaTime)
{
    if (_deltaTime <= 0.0f)
    {
        return;
    }

    CheckPlayerCollision();

    GameObject::Update(_deltaTime);
}

void Spike::Draw()
{
    GameObject::Draw();
}

void Spike::CheckPlayerCollision()
{
    auto collisions = mpCollider->GetCollisions(Tag::PLAYER);

    for (auto* playerObject : collisions)
    {
        if (playerObject == nullptr)
        {
            continue;
        }

        Player* player = dynamic_cast<Player*>(playerObject);

        if (player == nullptr)
        {
            continue;
        }

        // Playerをリスポーン位置へ戻す
        player->Respawn();

        break;
    }
}