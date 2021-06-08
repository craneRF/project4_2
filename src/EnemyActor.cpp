#include "EnemyActor.h"
#include "stdComponent.h"

void EnemyActor::createEnemy(GameActor* _parent, ofVec3f _pos, string _name)
{
	auto actor = _parent->addChild();
	actor->initialize(_pos, _name);
	auto moveCpnt = actor->addComponent<MoveComponent>();
	moveCpnt->setMoveVec({ 150.0f,0,0 });

	actor->drawfunc = [=]() {
		ofSetColor(ofColor::green);
		//ofDrawRectangle(ofVec3f(0, 0), 30, 30);
		ofDrawRectangle(ofVec3f(-15, -15), 30, 30);
	};

	auto coliisionCpnt = actor->addComponent<CollisionComponent>();
	coliisionCpnt->initialize(ofVec3f(0, 0), 30, 30, CollisionType::ENEMY_BULLET);
	coliisionCpnt->m_onCollisionFunc = bind(&onCollision, actor, std::placeholders::_1);
}