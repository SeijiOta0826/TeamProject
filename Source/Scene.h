#pragma once

class ObjectManager;

class Scene
{
public:
	Scene();
	virtual ~Scene();

	virtual void Initialize() = 0;					// 初期処理
	virtual void Finalize() = 0;					// 終了処理
	virtual void Update(float _deltaTime);			// 更新処理
	virtual void Draw();							// 描画処理

	ObjectManager* GetObjectManager() {return mpObjectManager;}

private:
	ObjectManager* mpObjectManager;	// ObjectManager(所有権はScene)
};
