#include "UITransform.h"

#include "ScreenConfig.h"

VECTOR UITransform::GetCenterPosition()
{
	const auto position = GetPosition();
	const auto anchor = GetAnchor();
	const auto anchorPosition = VGet(
		ScreenConfig::SCREEN_WIDTH * anchor.x,
		ScreenConfig::SCREEN_HEIGHT * anchor.y,
		0.0f
	);
	const auto worldCenterPosition = VAdd(
		position,
		anchorPosition
	);

	return worldCenterPosition;
}

VECTOR UITransform::GetPivotLocalPosition()
{
	return VGet(
		(mvPivot.x - 0.5f) * mvSize.x,
		(mvPivot.y - 0.5f) * mvSize.y,
		0.0f
	);
}