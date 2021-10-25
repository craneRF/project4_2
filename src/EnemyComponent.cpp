#include "ofApp.h"
#include "EnemyComponent.h"
#include "CollisionComponent.h"
#include "BoxComponent.h"
#include "SpriteComponent.h"
#include "EnemyType.h"

EnemyObject EnemyComponent::m_stdEnemy;
NomalEnemy EnemyComponent::m_nomalEnemy;
SmallEnemy EnemyComponent::m_smallEnemy;

EnemyComponent::EnemyComponent(GameActor * _gactor) :Component(_gactor, "Enemy")
{
	/*mp_epCpnt = _gactor->addComponent<EnemyPartsComponent>();*/
	auto boxCpnt = _gactor->addComponent<BoxComponent>();
	boxCpnt->initialize(ofVec3f(0, 0), _gactor->getComponent<SpriteComponent>()->ImageSize().x, _gactor->getComponent<SpriteComponent>()->ImageSize().y, CollisionType::ENEMY_OBJECT);
	boxCpnt->m_onCollisionFunc = bind(&EnemyComponent::onCollision, this, placeholders::_1);
}

EnemyComponent::~EnemyComponent()
{

}

void EnemyComponent::update()
{

}

void EnemyComponent::input()
{
}

void EnemyComponent::onCollision(CollisionComponent* _actor)
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
	enemyCpnt = actor->getComponent<EnemyComponent>();

	//画像の適用
	auto mp_sprCpnt = actor->addComponent<SpriteComponent>();
	mp_sprCpnt->TexName() = "Idling/" + enemyCpnt->getEnemy(_enemytype).ImageName;
	mp_sprCpnt->AlignPivotCenter();
}

void EnemyPartsComponent::CreateParts(EnemyType _enemytype)
{
	auto pmap = enemyCpnt->getEnemy(_enemytype).eParts;
	pmap.find("body")->second.ImageName;

}
