#include "PlayerShapeUI.h"

// -- 所有するUI -- //
#include "PlayerPieceUI.h"

// -- UIの生成用 -- //
#include "Master.h"
#include "SceneManager.h"
#include "Scene.h"
#include "UIManager.h"

#include "ObjectManager.h"	// Playerのアドレス取得用
#include "Player.h"

// -- Module -- //
#include "Transform.h"

void PlayerShapeUI::Init()
{
	LoadUIGraph("Resource/UI/外側.png");

	// -- piece生成 & 初期処理 -- //
	for (int row = 0;
		row < GameConfig::PLAYER_PIECE_SIZE;
		++row)
	{
		for (int column = 0;
			column < GameConfig::PLAYER_PIECE_SIZE;
			++column)
		{
			CreatePieceUI(column, row);
		}
	}

	mpConfirmUI =
		Master::mpSceneManager
		->GetCurrentScene()
		->GetUIManager()
		->CreateUI<UI>();
	// Todo : 画像が決まり次第ロード

	// -- 親子の設定 -- //
	this->AddChild(mpConfirmUI);
	mpConfirmUI->SetParent(this);

	mpBackUI =
		Master::mpSceneManager
		->GetCurrentScene()
		->GetUIManager()
		->CreateUI<UI>();
	// Todo : 画像が決まり次第ロード

	// -- 親子の設定 -- //
	this->AddChild(mpBackUI);
	mpBackUI->SetParent(this);

	// -- Playerのアドレス取得 -- //
	mpPlayer =
		Master::mpSceneManager
		->GetCurrentScene()
		->GetObjectManager()
		->FindObject<Player>();
}

void PlayerShapeUI::CreatePieceUI(int _column, int _row)
{
	// -- PieceUIの生成 -- //
	auto pieceUI =
		Master::mpSceneManager
		->GetCurrentScene()
		->GetUIManager()
		->CreateUI<PlayerPieceUI>();

	if (pieceUI == nullptr)
		return;

	pieceUI->LoadUIGraph("Resource/UI/内側.png");
	pieceUI->SetLayer(1);
	mPieceUI[_row][_column] = pieceUI;

	// -- 親子の設定 -- //
	this->AddChild(pieceUI);
	pieceUI->SetParent(this);

	// -- 初期座標の設定 -- //
	auto& pieceTransform = pieceUI->GetTransform();
	VECTOR size = pieceTransform.GetSize();
	VECTOR localPosition = VGet(
		(_column - 1) * size.x,
		(_row - 1) * size.y,
		0.0f
	);

	pieceTransform.SetPosition(localPosition);
}

void PlayerShapeUI::Update()
{
	/*if(mpConfirmUI->GetButton().IsClicked())
		this->*/
}

bool PlayerShapeUI::IsPieceSelected(int _x, int _y)
{
	return mPieceUI[_x][_y]->IsSelected();
}
