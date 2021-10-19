#include "ofApp.h"
#include "EnemyComponent.h"
#include "SpriteComponent.h"
#include "EnemyType.h"

EnemyObject EnemyComponent::m_stdEnemy;
NomalEnemy EnemyComponent::m_nomalEnemy;
SmallEnemy EnemyComponent::m_smallEnemy;

EnemyComponent::EnemyComponent(GameActor * _gactor) :Component(_gactor, "Enemy")
{
	//mp_epCpnt = _gactor->addComponent<EnemyPartsComponent>();
}

EnemyComponent::~EnemyComponent()
{

}

void EnemyComponent::update(float _deltatime)
{

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

void EnemyPartsComponent::CreateEnemyBody(GameActor * _parent, ofVec3f _pos, EnemyType _enemytype, string _name)
{
	//コンポーネントを生成
	auto actor = _parent;
	actor->initialize(_pos, _name);
	enemyCpnt = _parent->getComponent<EnemyComponent>();

	//画像の適用
	auto mp_sprCpnt = actor->addComponent<SpriteComponent>();
	mp_sprCpnt->setImage(ofApp::getInstance()->mp_imageManager->getContents("images/Idling/" + enemyCpnt->getEnemy(_enemytype).ImageName));
	mp_sprCpnt->AlignPivotCenter();
}

void EnemyPartsComponent::CreateParts(EnemyType _enemytype)
{
	auto pmap = enemyCpnt->getEnemy(_enemytype).eParts;
	pmap.find("body")->second.ImageName;

}
