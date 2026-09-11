#include "GameObject.h"

#include "Texture.h"
#include "Collider.h"
#include "Gravity.h"

#include "Master.h"
#include "SceneManager.h"
#include "Scene.h"
// #include "ObjectManager.h"
#include "CollisionManager.h"

#include "GameConfig.h"

GameObject::GameObject(std::string filename, VECTOR initPos)
	:Object2D(filename, initPos)
{ 
	// -- Objのサイズ調整(GameObjectとして) -- //
	mpTexture->SetSize(VGet(GameConfig::CELL_SIZE, GameConfig::CELL_SIZE, 0.0f));
	
	// -- コライダー初期設定 -- //
	mpCollider = new Collider(this);
	mpCollider->Initialize();
	mpCollider->SetHalfSize(VGet(GameConfig::CELL_SIZE / 2, GameConfig::CELL_SIZE / 2, 0.0f));

	// -- 重力システム初期設定 -- //
	mpGravity = new Gravity(this);
	mpGravity->Initialize();
}

GameObject::~GameObject() 
{
	// -- 所有するポインタの解放 -- //
	delete mpCollider;
	mpCollider = nullptr;

	delete mpGravity;
	mpGravity = nullptr;
}

void GameObject::Update(float _deltaTime)
{
	ResolveCollision();
}

void GameObject::Draw()
{
	Object2D::Draw();
}

void GameObject::ResolveCollision()
{
	mbGrounded = false;

	auto* collisionManager =
		Master::mpSceneManager
		->GetCurrentScene()
		->GetCollisionManager();

	if (collisionManager == nullptr
		|| !mpCollider->IsEnabled())
		return;

	auto tags = mpCollider->GetCollisionTag();

	for (auto tag : tags)
	{
		auto collisions = mpCollider->GetCollisions(tag);
		for (auto collision : collisions)
		{
			auto collider = collision->GetCollider();
			if (collider == nullptr)
				continue;

			CollisionInfo info;

			if (!collisionManager->GetBoxBoxCollision(
				mpCollider,
				collider,
				info))
			{
				continue;
			}

			if (info.normal.y < -0.5f)
			{
				mbGrounded = true;
			}

			VECTOR position = GetPosition();

			position = VAdd(
				position,
				VScale(info.normal, info.penetration)
			);

			SetPosition(position);
		}
	}
}