#include "BulletObject.h"
#include "stdComponent.h"

BulletObject::BulletObject()
{
	m_bParam.bulletName = "";
	m_bParam.imageName = "";
	m_bParam.generationSoundName = "";
	m_bParam.destroySoundName = "";
	m_bParam.scale = { 1.f,1.f };
	m_bParam.speed = 0.f;
	m_bParam.rotVal = 0.f;
	m_bParam.damage = 1;
}

void BulletObject::MoveToTarget(BulletComponent * _bulletComponent, MoveComponent * _moveComponent)
{
	// ベクトル作成
	ofVec3f direction = (_bulletComponent->getTarget() - _bulletComponent->gActor()->Pos()).normalize();

	_moveComponent->AddMovePos(direction * m_bParam.speed);
}

void BulletObject::RotateToTarget(BulletComponent * _bulletComponent, MoveComponent * _moveComponent, bool _isImmediately)
{
	// ベクトル作成
	ofVec3f direction = (_bulletComponent->getTarget() - _bulletComponent->gActor()->Pos()).normalize();

	// 回転
	// 進行方向の角度
	float angle = RAD_TO_DEG * atan2f(-direction.y, direction.x);
	angle = fmodf(angle + 360, 360);
	if (_isImmediately)
	{
		_bulletComponent->gActor()->RotAngle() = angle;
	}
	else
	{
		// ターゲットへの角度 - 現在の弾の角度
		float deltaAngle = angle - _bulletComponent->gActor()->RotAngle();

		if (fabsf(deltaAngle) < m_bParam.rotVal / 60)
		{
			_bulletComponent->gActor()->RotAngle() = angle;
		}
		else
		{
			if (deltaAngle > 0 && deltaAngle <= 180)
			{
				_moveComponent->AddMoveAngle(-m_bParam.rotVal);
			}
			else
			{
				_moveComponent->AddMoveAngle(m_bParam.rotVal);
			}
		}
	}
}

//NomalBullet
NomalBullet::NomalBullet() {
	initialize();
}

void NomalBullet::initialize()
{
	m_bParam.bulletName = "NormalBullet";
	m_bParam.scale = { 0.5,0.5 };
	m_bParam.speed = 600.f;
	//m_bParam.speed = 200.f;
	m_bParam.rotVal = 100.f;
	m_bParam.damage = 5;
	m_bParam.imageName = "6b71416463520028.png";
}

void NomalBullet::Move(BulletComponent * _bulletComponent, MoveComponent * _moveComponent)
{
	RotateToTarget(_bulletComponent, _moveComponent, false);
	//MoveToTarget(_bulletComponent, _moveComponent);
	_moveComponent->FrontMove(m_bParam.speed);
}

SmallBullet::SmallBullet()
{
	initialize();
}

void SmallBullet::initialize()
{
	m_bParam.bulletName = "SmallBullet";
	m_bParam.scale = { 0.2,0.2 };
	m_bParam.speed = 400.f;
	m_bParam.damage = 2;
	m_bParam.imageName = "Missile.png";
}

void SmallBullet::Move(BulletComponent * _bulletComponent, MoveComponent * _moveComponent)
{
	RotateToTarget(_bulletComponent, _moveComponent, true);
	MoveToTarget(_bulletComponent, _moveComponent);
}
