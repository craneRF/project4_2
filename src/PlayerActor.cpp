#include "PlayerActor.h"
#include "stdComponent.h"

GameActor* PlayerActor::createPlayer(GameActor* _parent, ofVec3f _pos, string _name) {
	auto actor = _parent->addChild();
	actor->initialize(_pos, _name);
	actor->setParam({ 500,500,0 }, { 0.1f,0.1f }, 0.0);

	auto playerCpnt = actor->addComponent<PlayerComponent>();

	auto moveCpnt = actor->addComponent<MoveComponent>();

	auto coliisionCpnt = actor->addComponent<CollisionComponent>();
	coliisionCpnt->initialize(ofVec3f(0, 0), 30, 30, CollisionType::PLAYER_OBJECT);
	coliisionCpnt->m_onCollisionFunc = bind(&PlayerComponent::onCollision, playerCpnt, std::placeholders::_1);

	return actor;
}