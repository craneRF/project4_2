#include "BulletObject.h"
#include "stdComponent.h"
#include "ofApp.h"

BulletObject::BulletObject()
{
	m_bParam.bulletName = "";
	m_bParam.imageName = "";
	m_bParam.generationSoundIndex = 12;
	m_bParam.destroySoundIndex = 11;
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

void BulletObject::ReflectRect(BulletComponent * _bulletComponent, MoveComponent * _moveComponent, const ofRectangle & _rect)
{
	const auto& wpos = _bulletComponent->gActor()->Pos();
	auto vec = _bulletComponent->getVec();

	// 上下で反射
	if (_rect.getBottom() < wpos.y)
	{
		auto delta = wpos.y - _rect.getBottom();
		_bulletComponent->gActor()->Pos().y = _rect.getBottom();
		//_bulletComponent->gActor()->Pos().y -= wpos.y - _rect.getBottom();
		vec.y *= -1;;
	}
	else if (_rect.getTop() > wpos.y)
	{
		auto delta = wpos.y - _rect.getTop();
		_bulletComponent->gActor()->Pos().y = _rect.getTop();
		//_bulletComponent->gActor()->Pos().y -= wpos.y - _rect.getTop();
		vec.y *= -1;;
	}

	// 左右で反射
	if (_rect.getRight() < wpos.x)
	{
		auto delta = wpos.x - _rect.getRight();
		_bulletComponent->gActor()->Pos().x = _rect.getRight();
		//_bulletComponent->gActor()->Pos().x -= wpos.x - _rect.getRight();
		vec.x *= -1;;
	}
	else if (_rect.getLeft() > wpos.x)
	{
		auto delta = wpos.x - _rect.getLeft();
		_bulletComponent->gActor()->Pos().x = _rect.getLeft();
		//_bulletComponent->gActor()->Pos().x -= wpos.x - _rect.getLeft();
		vec.x *= -1;;
	}

	_bulletComponent->SetVec(vec);
	_moveComponent->AddMovePos(vec * m_bParam.speed);
}

//NomalBullet
NomalBullet::NomalBullet()
{
	m_bParam.bulletName = "NormalBullet";
	m_bParam.scale = { 0.5,0.5 };
	m_bParam.speed = 600.f;
	m_bParam.generationSoundIndex = 13;
	m_bParam.rotVal = 100.f;
	m_bParam.damage = 5;
	m_bParam.imageName = "6b71416463520028.png";
}

void NomalBullet::initialize(BulletComponent * _bulletComponent)
{
}

void NomalBullet::Move(BulletComponent * _bulletComponent, MoveComponent * _moveComponent)
{
	RotateToTarget(_bulletComponent, _moveComponent, false);
	_moveComponent->FrontMove(m_bParam.speed);
}

SmallBullet::SmallBullet()
{
	m_bParam.bulletName = "SmallBullet";
	m_bParam.scale = { 0.2,0.2 };
	m_bParam.speed = 400.f;
	m_bParam.generationSoundIndex = 12;
	m_bParam.damage = 2;
	m_bParam.imageName = "Missile.png";
}

void SmallBullet::initialize(BulletComponent * _bulletComponent)
{
}

void SmallBullet::Move(BulletComponent * _bulletComponent, MoveComponent * _moveComponent)
{
	RotateToTarget(_bulletComponent, _moveComponent, true);
	MoveToTarget(_bulletComponent, _moveComponent);
}

BoundBullet::BoundBullet()
{
	m_bParam.bulletName = "BoundBullet";
	m_bParam.scale = { 0.2,0.2 };
	m_bParam.speed = 400.f;
	m_bParam.generationSoundIndex = 12;
	m_bParam.damage = 2;
	m_bParam.imageName = "Missile.png";
}

void BoundBullet::initialize(BulletComponent * _bulletComponent)
{
	_bulletComponent->getCollisionComponent()->mp_cobj->m_ctype = CollisionType::DEFAULT;
}

void BoundBullet::Move(BulletComponent * _bulletComponent, MoveComponent * _moveComponent)
{
	m_reflectRect.setFromCenter(_bulletComponent->getTarget(), 800, 500);
	ReflectRect(_bulletComponent, _moveComponent, m_reflectRect);
	if (ofApp::getInstance()->mp_inputManager->getButtonDown("Fire"))
	{
		_bulletComponent->gActor()->StateErace();
		_bulletComponent->getCollisionComponent()->mp_cobj->m_ctype = CollisionType::PLAYER_BULLET;
	}
}
