#pragma once

class GameObject;

class Gravity
{
public:
	Gravity(GameObject* _owner);
	~Gravity();

	void Initialize();
	void Finalize();

	void Update(float _deltaTime);

	// -- 有効フラグのアクセサ -- //
	void SetEnabled(bool _enable);
	bool IsEnabled() const;

private:
	void ResetVerticalVelocity();	// 落下速度を「0」にする

private:
	GameObject* mpOwner = nullptr;	// 付与先のObj

	bool mbEnabled = true;			// 有効であるかを示す
		
	float mfGravity = 0.0f;			// 重力加速度
	float mfVelocityY = 0.0f;		// 落下速度
};
