#include "ofApp.h"
#include "EnemyComponent.h"
#include "SpriteComponent.h"
#include "EnemyObject.h"

NomalEnemy EnemyComponent::m_nomalEnemy;

EnemyComponent::EnemyComponent(GameActor * _gactor):Component(_gactor,"Enemy")
{
	mp_sprCpnt = mp_gActor->addComponent<SpriteComponent>();
	mp_sprCpnt->setImage(ofApp::getInstance()->mp_imageManager->getContents("images/Idling/zeni.png"));
	mp_sprCpnt->AlignPivotCenter();
}

EnemyComponent::~EnemyComponent()
{
}

void EnemyComponent::update(float _deltatime)
{
	mp_sprCpnt->setImage(ofApp::getInstance()->mp_imageManager->getContents("images/Idling/zeni.png"));
}

void EnemyComponent::onCollision(CollisionComponent *)
{
}

ofVec3f EnemyComponent::getScale(int _enemytype)
{
	return m_nomalEnemy.m_eParam.scale;
}

void EnemyComponent::discriminantEnemyType(int _enemytype)
{
	
}
