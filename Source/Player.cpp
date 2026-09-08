#include "Player.h"

#include "Collider.h"
#include "Gravity.h" // ’Ç‰Á
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

	mpCollider = new Collider(this);
	mpCollider->Initialize();

	mpCollider->SetHalfSize(VGet(50.0f, 50.0f, 0.0f));

	// ’Ç‰Á
	mpGravity = new Gravity(this);
	mpGravity->Initialize();
}

Player::~Player()
{
	delete mpGravity;
	mpGravity = nullptr;

	delete mpCollider;
	mpCollider = nullptr;
}

void Player::Update(float _deltaTime)
{
	Move();
	mpGravity->Update(_deltaTime); // ’Ç‰Á
	ResolveStageCollision();
}

void Player::Draw()
{
	Object2D::Draw();
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

void Player::ResolveStageCollision() {
	auto* collisionManager =
		Master::mpSceneManager
		->GetCurrentScene()
		->GetCollisionManager();

	auto* collider = mpCollider;

	auto* stage =
		collider->GetCollision(Tag::BLOCK);

	if (stage == nullptr) {
		return;
	}

	auto StageObj =
		dynamic_cast<StageBlock*>(stage);

	auto* stageCollider =
		StageObj->GetCollider();

	if (stageCollider == nullptr) {
		return;
	}

	CollisionInfo info;

	if (!collisionManager->GetBoxBoxCollision(
		collider,
		stageCollider,
		info)) {
		return;
	}

	VECTOR position =
		this->GetPosition();

	position = VAdd(
		position,
		VScale(info.normal, info.penetration)
	);

	this->SetPosition(position);
}