#pragma once
#include <vector>
#include <utility>
#include <string>

class Module;
class ObjectManager;

enum class Tag
{
	None,

	UNNKO,
	PLAYER,
	PLAYER_CELL,
	BLOCK,
};

// コンポーネントを保持・管理するゲームオブジェクトの基底クラス
class GameObject
{
public:
	virtual ~GameObject() = default;

	virtual void Init() = 0;			// 初期化処理
	virtual void InitComponent() = 0;	// コンポーネント初期設定
	virtual void Finalize();			// GameObject & コンポーネント終了処理
	virtual void Update(float _deltaTime);		// 保有するコンポーネントの更新処理
	virtual void Draw();		// 保有するコンポーネントの描画処理

	// 自身にコンポーネントを追加する
	template <class T, class...Args>
	T* AddModule(Args&&...args) {
		static_assert(std::is_base_of_v<Module, T>,
			"T must derive from Component.");

		auto module = new T(std::forward<Args>(args)...);
		module->mpGameObject = this;
		
		mModules.push_back(module);

		return module;
	}

	// 自身に付与されている指定コンポーネントを取得
	template<class T>
	T* GetModule() {
		for (auto& module : mModules) {
			if (auto ptr = dynamic_cast<T*>(module)) return ptr;
		}

		return nullptr;
	}

	// 同Scene内のObjectManagerへのゲッター
	ObjectManager* GetObjectManager() { return mpObjectManager; }

	// 解放するかどうかのフラグアクセサ
	void Destroy() { mbDestroy = true; }
	bool IsDestroy() { return mbDestroy; }

	void SetTag(Tag _tag) { mTag = _tag; }
	Tag GetTag() const { return mTag; }

	bool IsGrounded() const { return mbGrounded; }

private:
	void ResolveCollision();

protected:
	virtual const char* GetModelFilename() const = 0;

private:
	friend class ObjectManager;
	ObjectManager* mpObjectManager;
	void Initialize(ObjectManager* _manager);

private:
	std::vector<Module*> mModules;	//所持しているコンポーネントのコンテナ

	bool mbDestroy = false;
	Tag mTag;

	bool mbGrounded = true;
};