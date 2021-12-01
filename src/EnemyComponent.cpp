#include "ofApp.h"
#include "EnemyComponent.h"
#include "CollisionComponent.h"
#include "BoxComponent.h"
#include "SpriteComponent.h"
#include "EnemyActor.h"
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
	auto enemyCpnt = actor->getComponent<EnemyComponent>();

	//画像の適用
	auto mp_sprCpnt = actor->addComponent<SpriteComponent>();
	mp_sprCpnt->initialize(enemyCpnt->getEnemy(_enemytype).ImageName);
	mp_sprCpnt->AlignPivotCenter();

	CreateParts(actor, _pos, _enemytype);
}

void EnemyPartsComponent::CreateParts(GameActor * _parent, ofVec3f _pos, EnemyType _enemytype)
{
	auto enemyCpnt = _parent->getComponent<EnemyComponent>();
	auto pmap = enemyCpnt->getEnemy(_enemytype).eParts;

 	for (auto& c : pmap)
	{
		auto parts = c.second;

		auto actor = _parent->addChild<GameActor>();
		actor->initialize(parts.Pos, parts.PartsName);
		actor->SetParam(parts.Pos, parts.Scale, parts.angle);

		auto mp_sprCpnt = actor->addComponent<SpriteComponent>();
		mp_sprCpnt->initialize(parts.ImageName);
		mp_sprCpnt->AlignPivotCenter();
	}
}