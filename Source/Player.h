#pragma once
#include "Object2D.h"
#include <array>

class Collider;
class Gravity; // �ǉ�

class Player : public Object2D
{
public:
	Player(std::string filename, VECTOR initPos);
	~Player();

	void Update(float _deltaTime) override;
	void Draw() override;

private:
	void Move();
	void ResolveStageCollision();	// ステージとの衝突判定を受け取り、移動を制限する処理

private:
	Collider* mpCollider;		// このオブジェクトが使用するコライダー
		
	float mfSpeed = 10.0f;		// 移動スピード(移動はPlayerくらいしかしないかな...と思ったのでPlayer持ち)
	void ResolveStageCollision();
	
	// �ό`��ʂ�`��
	void DrawTransformUI();
	void UpdateTransformUI();

	// �ό`���Collider���X�V
	void UpdateTransformCollider();

private:
	std::array<Collider*, 9> mColliders;

	Gravity* mpGravity; // �ǉ�

	float mCurrentAngle = 0.0f; // ���̊p�x�i�x���@�F0?360�j
	float mTargetAngle = 0.0f;  // �ڎw���p�x

	const float BLOCK_SIZE = 100.0f; // �u���b�N�̃T�C�Y�i����j
	float mMoveStepX = 0.0f; // �ړ��X�e�b�v�i����j

	void Rotate();
	bool mbIsTransforming = false; // �ǉ�

	// 3�~3�̌`��f�[�^
	bool mShape[3][3] = {};

	float mfSpeed = 10.0f;
};