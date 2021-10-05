#include "EnemyActor.h"
#include "stdComponent.h"

GameActor* EnemyActor::createEnemy(GameActor* _parent, ofVec3f _pos, string _name)
{
	auto actor = _parent->addChild();
	actor->initialize(_pos, _name);
	//actor->setParam(_pos, { 0.1f,0.1f });
	auto enemyCpnt = actor->addComponent<EnemyComponent>();

	auto imageSize = actor->getComponent<SpriteComponent>()->ImageSize();

	auto coliisionCpnt = actor->addComponent<CollisionComponent>();
	coliisionCpnt->initialize(ofVec3f(0, 0), imageSize.x, imageSize.y, CollisionType::ENEMY_OBJECT);
	coliisionCpnt->m_onCollisionFunc = bind(&EnemyComponent::onCollision, enemyCpnt, std::placeholders::_1);

	return actor;
}