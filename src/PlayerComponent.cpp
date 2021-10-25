#include "ofApp.h"
#include "PlayerComponent.h"
#include "SpriteComponent.h"
#include "CollisionComponent.h"
#include "BoxComponent.h"

PlayerComponent::PlayerComponent(GameActor * _gactor) :Component(_gactor, "Player")
{
	mp_sprCpnt = mp_gActor->addComponent<SpriteComponent>();
	mp_sprCpnt->TexName() = "Idling/Arrow.png";
	//mp_sprCpnt->setImage(ofApp::getInstance()->mp_imageManager->getContents("images/Idling/marine_icon.png"));
	mp_sprCpnt->AlignPivotCenter();

	auto boxCpnt = _gactor->addComponent<BoxComponent>();
	boxCpnt->initialize(ofVec3f(0, 0), _gactor->getComponent<SpriteComponent>()->ImageSize().x * 0.2f, _gactor->getComponent<SpriteComponent>()->ImageSize().y * 0.2f, CollisionType::PLAYER_OBJECT);
	//coliisionCpnt->initialize(ofVec3f(0, 0), 2067, 2067, CollisionType::PLAYER_OBJECT);
	//coliisionCpnt->initialize(ofVec3f(0, 0), 30, 30, CollisionType::PLAYER_OBJECT);
	boxCpnt->m_onCollisionFunc = bind(&PlayerComponent::onCollision, this, std::placeholders::_1);
}

PlayerComponent::~PlayerComponent()
{
}

void PlayerComponent::update()
{
	//mp_sprCpnt->setImage(ofApp::getInstance()->mp_imageManager->getContents("images/Idling/marine_icon.png"));
}

void PlayerComponent::input()
{
}

void PlayerComponent::onCollision(CollisionComponent* _other)
{

}
