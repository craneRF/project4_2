#include "PlayerActor.h"
#include "stdComponent.h"
#include "BoxComponent.h"

PlayerActor::PlayerActor(string _name)
	:GameActor(_name)
{
}

PlayerActor* PlayerActor::createPlayer(GameActor* _parent, ofVec3f _pos, BattleComponent* _battleCpnt, string _name) {
	auto actor = _parent->addChild<PlayerActor>();
	actor->Scale() = { 0.25f,0.25f };
	actor->initialize(_pos, _name);

	auto playerCpnt = actor->addComponent<PlayerComponent>();
	playerCpnt->Initialize(_battleCpnt);
	//auto moveCpnt = actor->addComponent<MoveComponent>();

	//auto imageSize = playerCpnt->GetImageSize();

	//auto boxCpnt = actor->addComponent<BoxComponent>();
	//boxCpnt->initialize(ofVec3f(0, 0), imageSize.x * 0.2f, imageSize.y * 0.2f, CollisionType::PLAYER_OBJECT);
	//boxCpnt->m_onCollisionFunc = bind(&PlayerComponent::onCollision, playerCpnt, std::placeholders::_1);

	return actor;
}


