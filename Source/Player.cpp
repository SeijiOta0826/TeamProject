#include "Player.h"
#include "Texture.h"

#include "Collider.h"
#include "Gravity.h" // 追加
#include "InputManager.h"

#include "Master.h"
#include "SceneManager.h"
#include "Scene.h"
#include "CollisionManager.h"

#include "StageBlock.h"

Player::Player(std::string filename, VECTOR initPos)
	:Object2D(filename, initPos)
{
	SetTag(Tag::PLAYER);

	// 3×3 = 9個のColliderを作成
	for (int i = 0; i < 9; i++)
	{
		mColliders[i] = new Collider(this);
		mColliders[i]->Initialize();
		mColliders[i]->SetHalfSize(
			VGet(50.0f, 50.0f, 0.0f)
		);
		mColliders[i]->SetEnabled(false);
	}

	// 初期状態は中央の1ブロックだけ有効
	mColliders[4]->SetEnabled(true);

	// 追加
	mpGravity = new Gravity(this);
	mpGravity->Initialize();

	// 初期形状
	mShape[1][1] = true;

	UpdateTransformCollider();
}

Player::~Player()
{
	delete mpGravity;
	mpGravity = nullptr;

	for (auto* collider : mColliders)
	{
		if (collider != nullptr)
		{
			collider->Finalize();
			delete collider;
		}
	}

	mColliders.fill(nullptr);
}

void Player::Update(float _deltaTime)
{
	// Eキーを押したら変形モードに入る
	if (InputManager::GetInstance().GetButtonDown(Button::Transform))
	{
		mbIsTransforming = true;
	}

	// 変形中かどうかで入力を切り替える
	if (mbIsTransforming)
	{
		UpdateTransformUI();
	}
	else
	{
		Move();

		// 通常時だけ重力を処理
		mpGravity->Update(_deltaTime);

		// StageBlockとの当たり判定
		ResolveStageCollision();
	}
}

void Player::Draw()
{
	// Player本体
	Object2D::Draw();

	// 追加されたブロックを描画
	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			// 中央はPlayer本体が描画されているので飛ばす
			if (x == 1 && y == 1)
			{
				continue;
			}

			// OFFのマスは描画しない
			if (!mShape[y][x])
			{
				continue;
			}

			const float blockSize = 100.0f;

			VECTOR position = GetPosition();

			position.x += (x - 1) * blockSize;
			position.y += (y - 1) * blockSize;

			// Playerと同じ画像を描画
			Texture* texture = GetTexture();

			if (texture != nullptr)
			{
				texture->SetPosition(position);
				texture->Draw();
			}
		}
	}

	// 変形画面
	if (mbIsTransforming)
	{
		DrawTransformUI();
	}
}

void Player::Move()
{
	VECTOR inputDirection = VGet(0.0f, 0.0f, 0.0f);

	inputDirection.x += InputManager::GetInstance().GetAxis(Axis::MoveX);
	inputDirection.y += InputManager::GetInstance().GetAxis(Axis::MoveY);

	if (VSize(inputDirection) == 0.0f)
		return;

	VECTOR moveAmount = VScale(inputDirection, mfSpeed);

	VECTOR nextPos = VAdd(
		GetPosition(),
		moveAmount
	);

	SetPosition(nextPos);
}

void Player::ResolveStageCollision()
{
	auto* collisionManager =
		Master::mpSceneManager
		->GetCurrentScene()
		->GetCollisionManager();

	for (auto* collider : mColliders)
	{
		if (collider == nullptr || !collider->IsEnabled())
		{
			continue;
		}

		auto* stage =
			collider->GetCollision(Tag::BLOCK);

		if (stage == nullptr)
		{
			continue;
		}

		auto* stageObj =
			dynamic_cast<StageBlock*>(stage);

		if (stageObj == nullptr)
		{
			continue;
		}

		auto* stageCollider =
			stageObj->GetCollider();

		if (stageCollider == nullptr)
		{
			continue;
		}

		CollisionInfo info;

		if (!collisionManager->GetBoxBoxCollision(
			collider,
			stageCollider,
			info))
		{
			continue;
		}

		VECTOR position = GetPosition();

		position = VAdd(
			position,
			VScale(info.normal, info.penetration)
		);

		SetPosition(position);
	}
}

void Player::DrawTransformUI()
{
	int screenWidth;
	int screenHeight;

	GetDrawScreenSize(&screenWidth, &screenHeight);

	const int cellSize = 100;
	const int gridSize = cellSize * 3;

	const int startX = (screenWidth - gridSize) / 2;
	const int startY = (screenHeight - gridSize) / 2;

	// 背景
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);

	DrawBox(
		0,
		0,
		screenWidth,
		screenHeight,
		GetColor(0, 0, 0),
		TRUE
	);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// 3×3
	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			int left = startX + x * cellSize;
			int top = startY + y * cellSize;
			int right = left + cellSize;
			int bottom = top + cellSize;

			int color;

			if (mShape[y][x])
			{
				// ON
				color = GetColor(255, 255, 255);
			}
			else
			{
				// OFF
				color = GetColor(80, 80, 80);
			}

			DrawBox(
				left,
				top,
				right,
				bottom,
				color,
				TRUE
			);

			// 枠
			DrawBox(
				left,
				top,
				right,
				bottom,
				GetColor(255, 255, 255),
				FALSE
			);
		}
	}

	DrawString(
		startX,
		startY - 40,
		"変形",
		GetColor(255, 255, 255)
	);
}

void Player::UpdateTransformUI()
{
	int mouseX = InputManager::GetInstance().GetMouse().GetX();
	int mouseY = InputManager::GetInstance().GetMouse().GetY();

	const int cellSize = 100;
	const int gridSize = cellSize * 3;

	int screenWidth;
	int screenHeight;

	GetDrawScreenSize(&screenWidth, &screenHeight);

	const int startX = (screenWidth - gridSize) / 2;
	const int startY = (screenHeight - gridSize) / 2;

	// マウスが3×3の範囲内にあるか
	if (mouseX >= startX &&
		mouseX < startX + gridSize &&
		mouseY >= startY &&
		mouseY < startY + gridSize)
	{
		// 何列目・何行目をクリックしたか計算
		int cellX = (mouseX - startX) / cellSize;
		int cellY = (mouseY - startY) / cellSize;

		// 左クリックされたらON/OFF切り替え
		if (InputManager::GetInstance().GetMouse().IsDown(MOUSE_INPUT_LEFT))
		{
			mShape[cellY][cellX] = !mShape[cellY][cellX];
		}
	}

	// Enterで変形を確定
	if (InputManager::GetInstance().GetButtonDown(Button::Confirm))
	{
		UpdateTransformCollider();

		// 変形によって大きくなった場合のめり込み防止
		VECTOR position = GetPosition();
		position.y -= 10.0f;
		SetPosition(position);

		mbIsTransforming = false;
	}
}

void Player::UpdateTransformCollider()
{
	const float blockSize = 100.0f;

	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			int index = y * 3 + x;

			Collider* collider = mColliders[index];

			if (collider == nullptr)
			{
				continue;
			}

			// 選択されているマスだけColliderを有効にする
			collider->SetEnabled(mShape[y][x]);

			if (!mShape[y][x])
			{
				continue;
			}

			// 3×3の中心をPlayerの位置にする
			float offsetX =
				(x - 1) * blockSize;

			float offsetY =
				(y - 1) * blockSize;

			// Colliderを各マスの位置へ移動
			collider->SetOffset(
				VGet(
					offsetX,
					offsetY,
					0.0f
				)
			);

			// 1ブロック分のCollider
			collider->SetHalfSize(
				VGet(
					blockSize / 2.0f,
					blockSize / 2.0f,
					0.0f
				)
			);
		}
	}
}