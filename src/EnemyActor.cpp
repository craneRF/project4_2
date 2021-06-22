#include "EnemyActor.h"
#include "stdComponent.h"

void EnemyActor::createEnemy(GameActor* _parent, ofVec3f _pos, int _enemytype, string _name)
{
	auto actor = _parent->addChild();
	auto enemyCpnt = actor->addComponent<EnemyComponent>();

	actor->initialize(_pos, _name);
	actor->setParam(_pos, enemyCpnt->getScale(Nomal));

	auto coliisionCpnt = actor->addComponent<CollisionComponent>();
	coliisionCpnt->initialize(ofVec3f(0, 0), 30, 30, CollisionType::ENEMY_BULLET);
	coliisionCpnt->m_onCollisionFunc = bind(&EnemyComponent::onCollision, enemyCpnt, std::placeholders::_1);
}