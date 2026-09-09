#pragma once

/* memo : 
* ゲームの重要な各種値の設定クラス
*/
class GameConfig
{
public:
	static constexpr float CELL_SIZE = 80.0f;	// マスの大きさ(例 1.0fの場合、1.0f × 1.0fのマス目になる)

	static constexpr float GLAVITY = 9.8f;		// 重力加速度
};