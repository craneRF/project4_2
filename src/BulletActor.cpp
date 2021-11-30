#include "stdComponent.h"
#include "ofApp.h"
#include "BulletActor.h"
#include "BulletObject.h"

BulletActor * BulletActor::createBullet(GameActor * _parent, ofVec3f _pos, ofVec3f _target, BulletType _bulletType)
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

	// �e�R���|�[�l���g
	auto bulletCpnt = actor->addComponent<BulletComponent>();
	bulletCpnt->initialize(_target, _bulletType);

	// �����蔻��R���|�[�l���g
	auto coliisionCpnt = actor->addComponent<CollisionComponent>();
	coliisionCpnt->m_onCollisionFunc = bind(&BulletComponent::onCollision, bulletCpnt, std::placeholders::_1);

	return actor;
}

BulletActor* BulletActor::createPlayerBullet(GameActor* _parent, ofVec3f _pos, ofVec3f _target, BulletType _bulletType)
{
	// �e�A�N�^�[�쐬
	auto actor = createBullet(_parent, _pos, _target, _bulletType);

	// �摜�T�C�Y�擾
	auto imageSize = actor->getComponent<SpriteComponent>()->ImageSize();

	auto coliisionCpnt = actor->getComponent<CollisionComponent>();
	coliisionCpnt->initialize(ofVec3f(0, 0), imageSize.x, imageSize.y, CollisionType::PLAYER_BULLET);

	return actor;
}

BulletActor* BulletActor::createEnemyBullet(GameActor* _parent, ofVec3f _pos, ofVec3f _target, BulletType _bulletType)
{
	// �e�A�N�^�[�쐬
	auto actor = createBullet(_parent, _pos, _target, _bulletType);

	// �摜�T�C�Y�擾
	auto imageSize = actor->getComponent<SpriteComponent>()->ImageSize();

	auto coliisionCpnt = actor->getComponent<CollisionComponent>();
	coliisionCpnt->initialize(ofVec3f(0, 0), imageSize.x, imageSize.y, CollisionType::ENEMY_BULLET);

	return actor;
}