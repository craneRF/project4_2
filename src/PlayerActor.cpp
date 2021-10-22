#include "PlayerActor.h"
#include "stdComponent.h"

PlayerActor* PlayerActor::createPlayer(GameActor* _parent, ofVec3f _pos, string _name) {
	auto actor = _parent->addChild<PlayerActor>();
	actor->Scale() = { 0.25f,0.25f };
	actor->initialize(_pos, _name);

	auto playerCpnt = actor->addComponent<PlayerComponent>();

	auto moveCpnt = actor->addComponent<MoveComponent>();

	auto imageSize = playerCpnt->GetImageSize();

	auto coliisionCpnt = actor->addComponent<CollisionComponent>();
	coliisionCpnt->initialize(ofVec3f(0, 0), imageSize.x * 0.2f, imageSize.y * 0.2f, CollisionType::PLAYER_OBJECT);
	coliisionCpnt->m_onCollisionFunc = bind(&PlayerComponent::onCollision, playerCpnt, std::placeholders::_1);

	return actor;
}


