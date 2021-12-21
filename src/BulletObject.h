#pragma once
#include "ofMain.h"

class BulletComponent;
class MoveComponent;

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
