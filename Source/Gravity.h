#pragma once // 追加

class Object2D;

class Gravity
{
public:
	Gravity(Object2D* _owner);
	~Gravity();

	void Initialize();
	void Finalize();

	void Update(float _deltaTime);

	void SetEnable(bool _enable);
	bool IsEnable() const;

private:
	Object2D* mpOwner = nullptr;	// 付与先のObj

	bool mbEnable = true;					// 有効であるかを示す
		
	float mfGravity = 0.0f;				// 重力加速度
	float mfVelocityY = 0.0f;				// 落下速度
};
