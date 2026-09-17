#include "Graphic.h"

#include "Master.h"
#include "ResourceManager.h"

#include "GameObject.h"
#include "Transform.h"

#include "GameConfig.h"

Graphic::Graphic(std::string _filename)
{
	// -- 画像ロード -- //
	mnGraphHandle =
		Master::mpResource->LoadGraphics(_filename);

	// -- 画像のサイズ取得 -- //
	int size_x;
	int size_y;
	GetGraphSize(mnGraphHandle, &size_x, &size_y);

	mvSize.x = static_cast<float>(size_x);
	mvSize.y = static_cast<float>(size_y);
}

void Graphic::Initialize()
{
	// -- GameObjectとしての拡縮値の取得 -- //
	auto transform = mpGameObject->GetModule<Transform>();
	if (transform == nullptr)
		return;

	VECTOR scale = VGet(0.0f, 0.0f, 0.0f);
	scale.x = GameConfig::CELL_SIZE / mvSize.x;
	scale.y = GameConfig::CELL_SIZE / mvSize.y;

	transform->SetScale(scale);
}

void Graphic::Draw()
{
	auto transfrom = mpGameObject->GetModule<Transform>();
	if (mnGraphHandle == -1 || transfrom == nullptr)
		return;

	const auto position = transfrom->GetPosition();
	const auto rotation = transfrom->GetRotation();
	const auto scale = transfrom->GetScale();

	DrawRotaGraph3(
		static_cast<int>(position.x),
		static_cast<int>(position.y),
		static_cast<int>(mvSize.x),
		static_cast<int>(mvSize.y),
		scale.x,
		scale.y,
		rotation.z,
		mnGraphHandle,
		TRUE,
		FALSE
	);
}