#include "GameObject.h"

#include "Texture.h"
#include "Collider.h"
#include "Gravity.h"

#include "GameConfig.h"

GameObject::GameObject(std::string filename, VECTOR initPos)
	:Object2D(filename, initPos)
{ 
	// -- Objのサイズ調整(GameObjectとして) -- //
	mpTexture->SetSize(VGet(GameConfig::CELL_SIZE, GameConfig::CELL_SIZE, 0.0f));
	
	// -- コライダー初期設定 -- //
	mpCollider = new Collider(this);
	mpCollider->Initialize();
	mpCollider->SetHalfSize(VGet(GameConfig::CELL_SIZE, GameConfig::CELL_SIZE, 0.0f));

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

}

void GameObject::Draw()
{
	Object2D::Draw();
}


