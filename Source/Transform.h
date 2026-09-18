#pragma once
#include "Module.h"

#include <DxLib.h>

// GameObjectの位置・回転・拡大縮小を管理する
class Transform : public Module
{
public:
	Transform() = default;
	virtual ~Transform() = default;

	void SetPosition(const VECTOR& _position) { mvPosition = _position; }
	const VECTOR& GetPosition() const{ return mvPosition; }

	void SetRotation(const VECTOR& _rotation) { mvRotation = _rotation; }
	const VECTOR& GetRotation() const { return mvRotation; }

	void SetScale(const VECTOR& _scale) { mvScale = _scale; }
	const VECTOR& GetScale() const { return mvScale; }
private:
	VECTOR mvPosition = VGet(0.0f, 0.0f, 0.0f);
	VECTOR mvRotation = VGet(0.0f, 0.0f, 0.0f);
	VECTOR mvScale = VGet( 1.0f, 1.0f, 1.0f );
};