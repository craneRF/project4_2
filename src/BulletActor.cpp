#include "stdComponent.h"
#include "ofApp.h"
#include "BulletActor.h"
#include "BulletObject.h"

BulletActor * BulletActor::createBullet(GameActor * _parent, ofVec3f _pos, ofVec3f _target, BulletType _bulletType)
{
	// 弾パラメータ取得
	BulletParam param = BulletComponent::getBullet(_bulletType);

	// アクター作成
	auto actor = _parent->addChild<BulletActor>();
	actor->SetParam(_pos, param.scale);
	if (param.bulletName != "") {
		actor->initialize(_pos, param.bulletName);
	}
	else {
		actor->initialize(_pos, "");
	}

	// 弾コンポーネント
	auto bulletCpnt = actor->addComponent<BulletComponent>();
	bulletCpnt->initialize(_target, _bulletType);

	// 当たり判定コンポーネント
	auto coliisionCpnt = actor->addComponent<CollisionComponent>();
	coliisionCpnt->m_onCollisionFunc = bind(&BulletComponent::onCollision, bulletCpnt, std::placeholders::_1);

	return actor;
}

BulletActor* BulletActor::createPlayerBullet(GameActor* _parent, ofVec3f _pos, ofVec3f _target, BulletType _bulletType)
{
	// 弾アクター作成
	auto actor = createBullet(_parent, _pos, _target, _bulletType);

	// 画像サイズ取得
	auto imageSize = actor->getComponent<SpriteComponent>()->ImageSize();

	auto coliisionCpnt = actor->getComponent<CollisionComponent>();
	coliisionCpnt->initialize(ofVec3f(0, 0), imageSize.x, imageSize.y, CollisionType::PLAYER_BULLET);

	return actor;
}

BulletActor* BulletActor::createEnemyBullet(GameActor* _parent, ofVec3f _pos, ofVec3f _target, BulletType _bulletType)
{
	// 弾アクター作成
	auto actor = createBullet(_parent, _pos, _target, _bulletType);

	// 画像サイズ取得
	auto imageSize = actor->getComponent<SpriteComponent>()->ImageSize();

	auto coliisionCpnt = actor->getComponent<CollisionComponent>();
	coliisionCpnt->initialize(ofVec3f(0, 0), imageSize.x, imageSize.y, CollisionType::ENEMY_BULLET);

	return actor;
}