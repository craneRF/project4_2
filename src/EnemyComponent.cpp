#include "ofApp.h"
#include "EnemyComponent.h"
#include "SpriteComponent.h"
#include "EnemyType.h"

EnemyObject EnemyComponent::m_stdEnemy;
NomalEnemy EnemyComponent::m_nomalEnemy;
SmallEnemy EnemyComponent::m_smallEnemy;

EnemyComponent::EnemyComponent(GameActor * _gactor) :Component(_gactor, "Enemy")
{
	mp_sprCpnt = mp_gActor->addComponent<SpriteComponent>();
	mp_sprCpnt->setImage(ofApp::getInstance()->mp_imageManager->getContents("images/Idling/" + getEnemy(m_EnemyType).ImageName));
	mp_sprCpnt->AlignPivotCenter();
}

EnemyComponent::~EnemyComponent()
{

}

void EnemyComponent::update(float _deltatime)
{
	mp_sprCpnt->setImage(ofApp::getInstance()->mp_imageManager->getContents("images/Idling/" + getEnemy(m_EnemyType).ImageName));
}

void EnemyComponent::onCollision(CollisionComponent *)
{
}

EnemyParam EnemyComponent::getEnemy(int _enemytype)
{
	switch (_enemytype)
	{
	case NONE:
		return m_stdEnemy.m_eParam;
	case Nomal:
		return m_nomalEnemy.m_eParam;
	case Small:
		return m_smallEnemy.m_eParam;
	}
}
