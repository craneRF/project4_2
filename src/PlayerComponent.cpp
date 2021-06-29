#include "ofApp.h"
#include "PlayerComponent.h"
#include "SpriteComponent.h"
#include "CollisionComponent.h"

PlayerComponent::PlayerComponent(GameActor * _gactor) :Component(_gactor, "Player")
{
	mp_sprCpnt = mp_gActor->addComponent<SpriteComponent>();
	mp_sprCpnt->setImage(ofApp::getInstance()->mp_imageManager->getContents("images/Idling/marine_icon.png"));
	mp_sprCpnt->AlignPivotCenter();
}

PlayerComponent::~PlayerComponent()
{
}

void PlayerComponent::update(float _deltatime)
{
	mp_sprCpnt->setImage(ofApp::getInstance()->mp_imageManager->getContents("images/Idling/marine_icon.png"));
}

void PlayerComponent::onCollision(CollisionComponent* _other)
{

}
