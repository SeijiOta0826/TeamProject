#pragma once

class Scene;

enum class SCENE_TYPE
{
	SCENE_NONE = 0,   // 定義なし
	GAME_SCENE = 1,
};

class SceneManager
{
public:
	SceneManager();
	~SceneManager() = default;
	
	void Initialize();	// 初期化処理
	void Update(float _deltaTime);		// 更新処理
	void Draw();		// 描画処理
	void Finalize();	// 終了処理

	void ChangeSceneIfNeeded();	// シーン遷移（切り替え処理）が必要な状態なら遷移処理する
	void SetNextScene(SCENE_TYPE next) { mnNextSceneType = next;}	// 次に遷移するシーンの設定

	Scene* GetCurrentScene() { return mpCurrentScene; }			// 現在シーンの取得
	SCENE_TYPE GetCurrentSceneType() { return mnSceneType; }	//シーンタイプの取得関数

private:
	SCENE_TYPE mnSceneType;      // 現在シーンのタイプ
	SCENE_TYPE mnNextSceneType;  // 次シーンのタイプ
	Scene* mpCurrentScene;       // 現在シーンのポインタ
};