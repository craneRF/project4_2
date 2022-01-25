#pragma once
#include "ofMain.h"

class BulletComponent;
class MoveComponent;

enum class BulletType
{
	Nomal,
	Small,
	Big,
	KeyGuard,
	TypeNum,
};

struct BulletParam
{
	string bulletName;			// ���O
	string imageName;			// �摜��
	int generationSoundIndex;	// �������ɖ炷�����t�@�C���̃C���f�b�N�X
	int destroySoundIndex;		// ���Ŏ��ɖ炷�����t�@�C���̃C���f�b�N�X
	ofVec3f scale;				// �傫��
	float speed;				// �ړ��̑���
	float rotVal;				// ��]�̑���
	int damage;					// �_���[�W
};

class BulletObject
{
public:
	BulletObject();
	virtual ~BulletObject() {};

	virtual void initialize(BulletComponent * _bulletComponent) {};
	virtual void Move(BulletComponent* _bulletComponent, MoveComponent* _moveComponent) {};

	BulletParam m_bParam;

protected:
	void MoveToTarget(BulletComponent* _bulletComponent, MoveComponent* _moveComponent);
	void RotateToTarget(BulletComponent* _bulletComponent, MoveComponent* _moveComponent, bool _isImmediately);
	void ReflectRect(BulletComponent* _bulletComponent, MoveComponent* _moveComponent, const ofRectangle& _rect);
};

class NomalBullet : public BulletObject
{
public:
	NomalBullet();
	virtual void initialize(BulletComponent * _bulletComponent);
	virtual void Move(BulletComponent* _bulletComponent, MoveComponent* _moveComponent);
};

class SmallBullet final : public BulletObject
{
private:

public:
	SmallBullet();
	virtual void initialize(BulletComponent * _bulletComponent);
	virtual void Move(BulletComponent* _bulletComponent, MoveComponent* _moveComponent);
};

class BoundBullet final : public BulletObject
{
private:
	ofRectangle m_reflectRect;

public:
	BoundBullet();
	virtual void initialize(BulletComponent * _bulletComponent);
	virtual void Move(BulletComponent* _bulletComponent, MoveComponent* _moveComponent);
};

class KeyGuardBullet final : public BulletObject
{
private:
	string m_needKey = "Bomb";

public:
	KeyGuardBullet();
	virtual void initialize(BulletComponent * _bulletComponent);
	virtual void Move(BulletComponent* _bulletComponent, MoveComponent* _moveComponent);
};
