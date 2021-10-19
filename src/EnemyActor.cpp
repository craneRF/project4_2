#include "stdComponent.h"
#include "ofApp.h"
#include "EnemyActor.h"
#include "EnemyObject.h"
#include "EnemyType.h"
 
string EnemyActor::m_EnemyName = "";

EnemyActor* EnemyActor::createEnemy(GameActor* _parent, ofVec3f _pos, EnemyType _enemytype, string _name)
{
	auto actor = _parent->addChild<EnemyActor>();
	auto enemyCpnt = actor->addComponent<EnemyComponent>();
	enemyCpnt->setEnemyType(_enemytype);

	actor->initialize(_pos, _name);
	actor->setParam(_pos, enemyCpnt->getEnemy(_enemytype).scale);

	enemyCpnt->mp_epCpnt->CreateEnemyBody(actor, _pos, _enemytype);

	////�R���|�[�l���g�𐶐�
	//auto actor = _parent;
	//actor->initialize(_pos, _name);
	//enemyCpnt = actor->getComponent<EnemyComponent>();

	////�摜�̓K�p
	//auto mp_sprCpnt = actor->addComponent<SpriteComponent>();
	//mp_sprCpnt->setImage(ofApp::getInstance()->mp_imageManager->getContents("images/Idling/" + enemyCpnt->getEnemy(_enemytype).ImageName));
	//mp_sprCpnt->AlignPivotCenter();

	if (enemyCpnt->getEnemy(_enemytype).EnemyName != "") {
		m_EnemyName = enemyCpnt->getEnemy(_enemytype).EnemyName;
	}
	else {
		m_EnemyName = StrEnemyType(_enemytype);
	}

	auto imageSize = actor->getComponent<SpriteComponent>()->ImageSize();

	auto coliisionCpnt = actor->addComponent<CollisionComponent>();
	coliisionCpnt->initialize(ofVec3f(0, 0), imageSize.x, imageSize.y, CollisionType::ENEMY_OBJECT);
	coliisionCpnt->m_onCollisionFunc = bind(&EnemyComponent::onCollision, enemyCpnt, std::placeholders::_1);

	return actor;
}
