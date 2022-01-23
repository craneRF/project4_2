#include "stdComponent.h"
#include "ofApp.h"
#include "BulletActor.h"
#include "BulletObject.h"

BulletActor::BulletActor(string _name)
	: GameActor(_name)
{
}

GameActor * BulletActor::createBullet(GameActor * _parent, ofVec3f _pos, ofVec3f _target, BulletType _bulletType)
{
	// �e�p�����[�^�擾
	BulletParam param = BulletComponent::getBullet(_bulletType);

	// �A�N�^�[�쐬
	auto actor = _parent->addChild<BulletActor>();
	actor->SetParam(_pos, param.scale);
	if (param.bulletName != "") {
		actor->initialize(_pos, param.bulletName);
	}
	else {
		actor->initialize(_pos, "");
	}


	return actor;
}

GameActor* BulletActor::createPlayerBullet(GameActor* _parent, ofVec3f _pos, ofVec3f _target, const int _attack, BulletType _bulletType)
{
	// �e�A�N�^�[�쐬
	auto actor = createBullet(_parent, _pos, _target, _bulletType);
	// �e�R���|�[�l���g
	auto bulletCpnt = actor->addComponent<BulletComponent>();
	bulletCpnt->initialize(_target, _bulletType, CollisionType::PLAYER_BULLET, _attack);

	return actor;
}

GameActor* BulletActor::createEnemyBullet(GameActor* _parent, ofVec3f _pos, ofVec3f _target, const int _attack, BulletType _bulletType)
{
	// �e�A�N�^�[�쐬
	auto actor = createBullet(_parent, _pos, _target, _bulletType);
	// �e�R���|�[�l���g
	auto bulletCpnt = actor->addComponent<BulletComponent>();
	bulletCpnt->initialize(_target, _bulletType, CollisionType::ENEMY_BULLET, _attack);

	return actor;
}