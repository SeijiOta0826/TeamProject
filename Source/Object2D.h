#pragma once
#include "DxLib.h"
#include <string>

class Texture;

enum class Tag 
{
	None,

	UNNKO,
	PLAYER,
	PLAYER_CELL,
	BLOCK,
};

/* memo : 
* テクスチャー / ObjectManager間の橋渡しクラス。
* 特にObject2Dで付与している機能はない。
* 冗長気味
*/

class Object2D
{
public:
	Object2D(std::string filename, VECTOR initPos);
	virtual ~Object2D();
	
	virtual void Update(float _deltaTime) = 0;
	virtual void Draw();

public:
	// -- 座標アクセサ -- //
	void SetPosition(VECTOR _pos);
	VECTOR GetPosition() { return mvPosition; }

	// -- 削除フラグアクセサ -- //
	void Destroy() { mbIsDestroy = true; }
	bool IsDestroy() { return mbIsDestroy; }

	// -- タグアクセサ - //
	void SetTag(Tag _tag) { mTag = _tag; }
	Tag GetTag() { return mTag; }

protected:
	Texture* mpTexture = nullptr;	// テクスチャー(画像描画クラス)のアドレス
		
	VECTOR mvPosition;		// 座標
	Tag mTag = Tag::None;	// Objを仕分けるためのタグ

private:
	bool mbIsDestroy = false;	// 削除フラグ
};
