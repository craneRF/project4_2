#include "ofApp.h"
#include "PlayerComponent.h"
#include "SpriteComponent.h"
#include "CollisionComponent.h"

PlayerComponent::PlayerComponent(GameActor * _gactor) :Component(_gactor, "Player")
{
	mp_sprCpnt = mp_gActor->addComponent<SpriteComponent>();
	mp_sprCpnt->TexName() = "Idling/Arrow.png";
	//mp_sprCpnt->setImage(ofApp::getInstance()->mp_imageManager->getContents("images/Idling/marine_icon.png"));
	mp_sprCpnt->AlignPivotCenter();
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
