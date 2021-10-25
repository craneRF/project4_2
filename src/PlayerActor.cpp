#include "PlayerActor.h"
#include "stdComponent.h"

PlayerActor* PlayerActor::createPlayer(GameActor* _parent, ofVec3f _pos, string _name) {
	auto actor = _parent->addChild<PlayerActor>();
	actor->initialize(_pos, _name);
	//actor->setParam(_pos, { 0.1f,0.1f }, 0.0);

	auto playerCpnt = actor->addComponent<PlayerComponent>();

	auto moveCpnt = actor->addComponent<MoveComponent>();

	auto imageSize = actor->getComponent<SpriteComponent>()->ImageSize();
	actor->Scale() = { 300 / imageSize.x, 300 / imageSize.y };

	//auto coliisionCpnt = actor->addComponent<CollisionComponent>();
	//coliisionCpnt->initialize(ofVec3f(0, 0), imageSize.x * 0.2f, imageSize.y * 0.2f, CollisionType::PLAYER_OBJECT);
	////coliisionCpnt->initialize(ofVec3f(0, 0), 2067, 2067, CollisionType::PLAYER_OBJECT);
	////coliisionCpnt->initialize(ofVec3f(0, 0), 30, 30, CollisionType::PLAYER_OBJECT);
	//coliisionCpnt->m_onCollisionFunc = bind(&PlayerComponent::onCollision, playerCpnt, std::placeholders::_1);

	//auto boxCpnt = actor->addComponent<BoxComponent>();
	//boxCpnt->initialize(ofVec3f(0, 0), imageSize.x * 0.2f, imageSize.y * 0.2f, CollisionType::PLAYER_OBJECT);
	////coliisionCpnt->initialize(ofVec3f(0, 0), 2067, 2067, CollisionType::PLAYER_OBJECT);
	////coliisionCpnt->initialize(ofVec3f(0, 0), 30, 30, CollisionType::PLAYER_OBJECT);
	//boxCpnt->m_onCollisionFunc = bind(&PlayerComponent::onCollision, playerCpnt, std::placeholders::_1);

	return actor;
}


