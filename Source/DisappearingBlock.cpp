#include "DisappearingBlock.h"

#include "Player.h"
#include "Collider.h"
#include "Gravity.h"
#include "GameConfig.h"

DisappearingBlock::DisappearingBlock(
	std::string filename,
	VECTOR initPos
)
	: StageBlock(filename, initPos)
{
	// Playerとの衝突を検知
	mpCollider->AddCollisionTag(Tag::PLAYER);
}

void DisappearingBlock::Update(float _deltaTime)
{
	if (_deltaTime <= 0.0f)
		return;

	if (!mbIsDisappeared)
	{
		// Playerが現在ブロックに乗っているか確認
		bool isPlayerOnBlock = CheckPlayer();

		if (isPlayerOnBlock)
		{
			// Playerが乗っている間だけタイマーを進める
			mTimer++;

			// 消える前の警告
			if (mTimer >= DISAPPEAR_TIME - WARNING_TIME)
			{
				mbIsWarning = true;
			}

			// 指定時間乗っていたら消える
			if (mTimer >= DISAPPEAR_TIME)
			{
				Disappear();
			}
		}
		else
		{
			// Playerが降りたらカウントをリセット
			mTimer = 0;
			mbIsTriggered = false;
			mbIsWarning = false;
			mpPlayer = nullptr;
		}

		StageBlock::Update(_deltaTime);
	}
	else
	{
		if (mpPlayer != nullptr)
		{
			VECTOR blockPosition = GetPosition();
			VECTOR playerPosition = mpPlayer->GetPosition();

			float blockSize = GameConfig::CELL_SIZE;

			//  プレイヤーが消えたブロックを下方向に通過したか
			bool isPlayerPassed = playerPosition.y > blockPosition.y + blockSize;

			//  プレイヤーが消えたブロックから横方向に十分離れたか
			float distanceX = fabsf(playerPosition.x - blockPosition.x);

			bool isPlayerFarAway = distanceX > blockSize * 2.0f;

			// どちらかを満たしたら復活
			if (isPlayerPassed || isPlayerFarAway)
			{
				Respawn();
			}
		}
	}
}

void DisappearingBlock::Draw()
{
	if (mbIsDisappeared)
		return;

	if (mbIsWarning)
	{
		// 5フレームごとに点滅
		if ((mTimer / 5) % 2 == 0)
		{
			return;
		}
	}

	StageBlock::Draw();
}

bool DisappearingBlock::CheckPlayer()
{
	auto collisions = mpCollider->GetCollisions(Tag::PLAYER);

	for (auto* playerObject : collisions)
	{
		if (playerObject == nullptr)
			continue;

		Player* player = dynamic_cast<Player*>(playerObject);

		if (player == nullptr)
			continue;

		mpPlayer = player;
		mbIsTriggered = true;

		return true;
	}

	return false;
}

void DisappearingBlock::Disappear()
{
	mbIsDisappeared = true;
	mbIsWarning = false;
	mbIsPlayerLeft = false;

	mTimer = 0;

	// ブロックの当たり判定を無効化
	mpCollider->SetEnabled(false);
}

void DisappearingBlock::Respawn()
{
	mbIsDisappeared = false;
	mbIsTriggered = false;
	mbIsWarning = false;
	mbIsPlayerLeft = false;

	mTimer = 0;
	mpPlayer = nullptr;

	// ブロックの当たり判定を有効化
	mpCollider->SetEnabled(true);
}