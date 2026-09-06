#pragma once

class ObjectManager;
class CollisionManager;

class Scene
{
public:
	Scene();
	virtual ~Scene();

	virtual void Initialize() = 0;					// 初期処理
	virtual void Finalize();						// 終了処理
	virtual void Update(float _deltaTime);			// 更新処理
	virtual void Draw();							// 描画処理

	ObjectManager* GetObjectManager() {return mpObjectManager;}
	CollisionManager* GetCollisionManager() {return mpCollisionManager;}

private:
	ObjectManager* mpObjectManager;			// ObjectManager(所有権はScene)
	CollisionManager* mpCollisionManager;	// CollisionManager(所有権はScene)
};
