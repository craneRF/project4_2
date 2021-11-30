#pragma once
#include "ofMain.h"

class BulletComponent;
class MoveComponent;

struct BulletParam
{
	string bulletName;
	string imageName;
	ofVec3f scale;
	float speed;
	float rotVal;
	int damage;
};

class BulletObject
{
public:
	BulletObject();
	virtual ~BulletObject() {};

	virtual void initialize() {};
	virtual void Move(BulletComponent* _bulletComponent, MoveComponent* _moveComponent) {};

	BulletParam m_bParam;

protected:
	void MoveToTarget(BulletComponent* _bulletComponent, MoveComponent* _moveComponent);
	void RotateToTarget(BulletComponent* _bulletComponent, MoveComponent* _moveComponent, bool _isImmediately);
};

class NomalBullet : public BulletObject
{
public:
	NomalBullet();
	virtual void initialize();
	virtual void Move(BulletComponent* _bulletComponent, MoveComponent* _moveComponent);
};

class SmallBullet final : public NomalBullet
{
public:
	SmallBullet();
	virtual void initialize();
	virtual void Move(BulletComponent* _bulletComponent, MoveComponent* _moveComponent);
};
