#pragma once
#include "FadeEffect.h"


class Scene;

enum class SCENE_TYPE
{
	SCENE_NONE = 0,		// 定義なし
	TITLE_SCENE = 1,    // タイトル
	STAGE_SELECT_SCENE = 2, // ステージセレクト
	GAME_SCENE = 3,		// GameScene
};

class SceneManager
{
public:
	SceneManager();
	~SceneManager() = default;
	
	void Initialize();					// 初期処理
	void Update(float _deltaTime);		// 更新処理
	void Draw();						// 描画処理
	void Finalize();					// 終了処理

	//void ChangeSceneIfNeeded();	// シーン遷移（切り替え処理）が必要な状態なら遷移処理する
	void SetNextScene(SCENE_TYPE next) { mnNextSceneType = next;}	// 次に遷移するシーンの設定

	Scene* GetCurrentScene() { return mpCurrentScene; }			// 現在シーンの取得
	SCENE_TYPE GetCurrentSceneType() { return mnSceneType; }	// シーンタイプの取得関数
	// 次のシーンを予約・フェードアウト開始
	void RequestScene(SCENE_TYPE _nextType);
	void SetStageNumber(int _stageNumber);
	int GetStageNumber() const;
	bool IsChangingScene() const { return mbIsChangingScene; }
	

private:

	//====Fade関連メンバ====//
	FadeEffect mFadeEffect;	//フェード用コンポジション
	bool mbIsChangingScene = false;	//遷移シーケンス実行中フラグ
	void ChangeSceneIfNeeded();
	
	//========================================================================================//
	//システムの状態遷移を示す重要な概念です。
	// 具体的には、タスクが実行可能状態、実行状態、待ち状態のいずれかに存在するかを示します。
	// タスクが実行可能状態にある場合、CPUがそのタスクに割り当てられ
	// すぐに処理を開始できる状態です。実行状態では、タスクが処理を実行中であり
	// 待ち状態では、タスクが入出力処理などに従事している間に待機しています. Google
	//========================================================================================//

	SCENE_TYPE mnSceneType;      // 現在シーンのタイプ
	SCENE_TYPE mnNextSceneType;  // 次シーンのタイプ
	Scene* mpCurrentScene;       // 現在シーンのポインタ

	int mnStageNumber = 1;		 //Stageの番号

	

};