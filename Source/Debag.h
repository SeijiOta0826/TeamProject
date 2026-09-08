#pragma once
#include <DxLib.h>
#include <sstream>
#include <vector>

/* memo : 
* デバック用の文言や、グリッド線、当たり判定の視覚化に用いるクラス。
* TitleSceneや、ResultSceneではあまり使わないことを見越して、静的メンバ関数で構成。
* 以下使用例、
* 
* GameScene.cpp
* Debag::Print("Playerの座標 : " , mpPlayer->GetPosition);
* 
* Player.cpp
* Debag::Print("衝突判定 : " , mpCollider->IsColliding());
* 
* Print関数は、int,float,string,char,VECTORなどの様々な型を引数に設定可能。
* 不便に感じる部分があれば太田が対応します
*/

class Debug
{
public:
	Debug() = default;
	~Debug() = default;

	static void Draw();		// 描画処理(main.cppの描画処理あたりに置く)
	static void Toggle();	// デバックモードの切り替え

	static bool IsEnable();

	template<typename... Args>
	static void Print(Args&&... _args)
	{
		if (!mbEnable)
			return;

		std::ostringstream stream;

		((stream << ... << std::forward<Args>(_args)));

		mTexts.push_back(stream.str());
	}

private:
	static void DrawGrid();
	static void DrawColliders();
	static void DrawGameTime();
	static void DrawTexts();

private:
	static bool mbEnable;						// デバックモードのON / OFFを示す
	static std::vector<std::string> mTexts;		// Print()で指定された文字列のコンテナ
};