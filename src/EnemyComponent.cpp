#include "ofApp.h"
#include "EnemyComponent.h"
#include "SpriteComponent.h"
#include "EnemyObject.h"

NomalEnemy EnemyComponent::m_nomalEnemy;
SmallEnemy EnemyComponent::m_smallEnemy;

EnemyComponent::EnemyComponent(GameActor * _gactor) :Component(_gactor, "Enemy")
{
	mp_sprCpnt = mp_gActor->addComponent<SpriteComponent>();
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

EnemyParam EnemyComponent::getEnemy(int _enemytype)
{
	switch (_enemytype)
	{
	case Nomal:
		mp_sprCpnt->setImage(ofApp::getInstance()->mp_imageManager->getContents("images/Idling/zeni.png"));
		mp_sprCpnt->AlignPivotCenter();
		return m_nomalEnemy.m_eParam;
	case Small:
		mp_sprCpnt->setImage(ofApp::getInstance()->mp_imageManager->getContents("images/Idling/zeni.png"));
		mp_sprCpnt->AlignPivotCenter();
		return m_smallEnemy.m_eParam;
	}
}

void EnemyComponent::discriminantEnemyType(int _enemytype)
{

}
