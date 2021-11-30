#include "ofApp.h"
#include "AttackActor.h"
#include "stdComponent.h"

AttackActor * AttackActor::createAtack(GameActor * _parent, ofVec3f _pos, string _name)
{
	auto actor = _parent->addChild<AttackActor>();
	actor->initialize(_pos, _name);
	actor->SetParam(_pos, {1.f,1.f});

	auto mp_sprCpnt = actor->addComponent<SpriteComponent>();
	mp_sprCpnt->initialize("");
	mp_sprCpnt->AlignPivotCenter();

	auto imageSize = actor->getComponent<SpriteComponent>()->ImageSize();

	auto coliisionCpnt = actor->addComponent<CollisionComponent>();
	coliisionCpnt->initialize(ofVec3f(0, 0), imageSize.x, imageSize.y, CollisionType::ENEMY_OBJECT);
	//coliisionCpnt->m_onCollisionFunc = bind(&EnemyComponent::onCollision, enemyCpnt, std::placeholders::_1);
	return actor;
}
