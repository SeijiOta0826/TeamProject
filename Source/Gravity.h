#pragma once // ’Ç‰Á

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
	Object2D* mpOwner;

	bool mbEnable;

	float mfGravity;
	float mfVelocityY;
};
