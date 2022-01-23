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
	string bulletName;			// 名前
	string imageName;			// 画像名
	int generationSoundIndex;	// 生成時に鳴らす音声ファイルのインデックス
	int destroySoundIndex;		// 消滅時に鳴らす音声ファイルのインデックス
	ofVec3f scale;				// 大きさ
	float speed;				// 移動の速さ
	float rotVal;				// 回転の速さ
	int damage;					// ダメージ
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
